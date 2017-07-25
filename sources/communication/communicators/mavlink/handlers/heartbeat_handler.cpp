#include "heartbeat_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QMap>
#include <QTimerEvent>
#include <QBasicTimer>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "db_facade.h"
#include "vehicle.h"

#include "mavlink_communicator.h"
#include "mavlink_mode_helper.h"

#include "telemetry_service.h"
#include "telemetry.h"

using namespace comm;
using namespace domain;

namespace
{
    dao::Vehicle::Type decodeType(uint8_t type)
    {
        switch (type) //TODO: other vehicles
        {
        case MAV_TYPE_FIXED_WING: return dao::Vehicle::FixedWing;
        case MAV_TYPE_TRICOPTER: return dao::Vehicle::Tricopter;
        case MAV_TYPE_QUADROTOR: return dao::Vehicle::Quadcopter;
        case MAV_TYPE_HEXAROTOR: return dao::Vehicle::Hexcopter;
        case MAV_TYPE_OCTOROTOR: return dao::Vehicle::Octocopter;
        case MAV_TYPE_COAXIAL: return dao::Vehicle::Coaxial;
        case MAV_TYPE_HELICOPTER: return dao::Vehicle::Helicopter;
        case MAV_TYPE_VTOL_DUOROTOR:
        case MAV_TYPE_VTOL_QUADROTOR:
        case MAV_TYPE_VTOL_TILTROTOR:
        case MAV_TYPE_VTOL_RESERVED2:
        case MAV_TYPE_VTOL_RESERVED3:
        case MAV_TYPE_VTOL_RESERVED4:
        case MAV_TYPE_VTOL_RESERVED5: return dao::Vehicle::Vtol;
        case MAV_TYPE_AIRSHIP:
        case MAV_TYPE_FREE_BALLOON: return dao::Vehicle::Airship;
        case MAV_TYPE_KITE: return dao::Vehicle::Kite;
        case MAV_TYPE_FLAPPING_WING: return dao::Vehicle::Ornithopter;
        case MAV_TYPE_GENERIC:
        default: return dao::Vehicle::UnknownType;
        }
    }

    Telemetry::SystemState decodeState(uint8_t state)
    {
        switch (state)
        {
        case MAV_STATE_BOOT:
            return Telemetry::Boot;
        case MAV_STATE_CALIBRATING:
            return Telemetry::Calibrating;
        case MAV_STATE_STANDBY:
            return Telemetry::Standby;
        case MAV_STATE_ACTIVE:
            return Telemetry::Active;
        case MAV_STATE_CRITICAL:
            return Telemetry::Critical;
        case MAV_STATE_EMERGENCY:
            return Telemetry::Emergency;
        case MAV_STATE_UNINIT:
        default:
            return Telemetry::UnknownState;
        }
    }
}

class HeartbeatHandler::Impl
{
public:
    db::DbFacade* dbFacade;
    domain::TelemetryService* telemetryService;
    QMap <int, QBasicTimer*> vehicleTimers;
    int sendTimer;
};

HeartbeatHandler::HeartbeatHandler(db::DbFacade* dbFacade,
                                   TelemetryService* telemetryService,
                                   MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    d(new Impl())
{
    d->dbFacade = dbFacade;
    d->telemetryService = telemetryService;

    d->sendTimer = this->startTimer(settings::Provider::value(
                                    settings::communication::heartbeat).toInt());
}

HeartbeatHandler::~HeartbeatHandler()
{
    for (QBasicTimer* timer: d->vehicleTimers.values()) delete timer;
}

void HeartbeatHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_HEARTBEAT) return;

    mavlink_heartbeat_t heartbeat;
    mavlink_msg_heartbeat_decode(&message, &heartbeat);

    int vehicleId = d->dbFacade->vehicleIdByMavId(message.sysid);

    dao::VehiclePtr vehicle = d->dbFacade->vehicle(vehicleId);

    if (!vehicle && settings::Provider::value(settings::communication::autoAdd).toBool())
    {
        vehicle = dao::VehiclePtr::create();
        vehicle->setMavId(message.sysid);
        vehicle->setType(dao::Vehicle::Auto);
        vehicle->setName(tr("Added"));
        d->dbFacade->save(vehicle);
    }

    if (vehicle)
    {
        bool changed  = false;

        if (!vehicle->isOnline())
        {
            vehicle->setOnline(true);
            changed = true;
        }

        if (!d->vehicleTimers.contains(vehicleId))
        {
            d->vehicleTimers[vehicleId] = new QBasicTimer();
        }
        d->vehicleTimers[vehicleId]->start(
                    settings::Provider::value(settings::communication::timeout).toInt(),
                    this);

        if (vehicle->type() == dao::Vehicle::Auto)
        {
            vehicle->setType(::decodeType(heartbeat.type));
            changed = true;
        }
        if (changed) d->dbFacade->vehicleChanged(vehicle);
    }

    Telemetry* node = d->telemetryService->mavNode(message.sysid);
    if (!node) return;

    node->setParameter({ Telemetry::Status, Telemetry::Armed },
                       heartbeat.base_mode & MAV_MODE_FLAG_DECODE_POSITION_SAFETY);
    node->setParameter({ Telemetry::Status, Telemetry::Auto },
                       heartbeat.base_mode & MAV_MODE_FLAG_DECODE_POSITION_AUTO);
    node->setParameter({ Telemetry::Status, Telemetry::Guided },
                       heartbeat.base_mode & MAV_MODE_FLAG_DECODE_POSITION_GUIDED);
    node->setParameter({ Telemetry::Status, Telemetry::Stabilized },
                       heartbeat.base_mode & MAV_MODE_FLAG_DECODE_POSITION_STABILIZE);
    node->setParameter({ Telemetry::Status, Telemetry::Manual },
                       heartbeat.base_mode & MAV_MODE_FLAG_DECODE_POSITION_MANUAL);

    node->setParameter({ Telemetry::Status, Telemetry::Mode },
                       ::decodeCustomMode(heartbeat.autopilot,
                                        heartbeat.type,
                                        heartbeat.custom_mode));
    node->setParameter({ Telemetry::Status, Telemetry::State },
                       ::decodeState(heartbeat.system_status));
    node->notify();
}

void HeartbeatHandler::sendHeartbeat()
{
    mavlink_message_t message;
    mavlink_heartbeat_t heartbeat;

    heartbeat.type = MAV_TYPE_GCS;

    mavlink_msg_heartbeat_encode(m_communicator->systemId(),
                                 m_communicator->componentId(),
                                 &message, &heartbeat);

    m_communicator->sendMessageAllLinks(message);
}

void HeartbeatHandler::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == d->sendTimer)
    {
        this->sendHeartbeat();
    }
    else
    {
        for (QBasicTimer* timer: d->vehicleTimers.values())
        {
            if (timer->timerId() != event->timerId()) continue;

            dao::VehiclePtr vehicle = d->dbFacade->vehicle(d->vehicleTimers.key(timer));
            if (vehicle) vehicle->setOnline(false);
            d->dbFacade->vehicleChanged(vehicle);
            timer->stop();
        }
    }
}
