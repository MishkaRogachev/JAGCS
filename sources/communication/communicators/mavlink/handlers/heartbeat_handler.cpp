#include "heartbeat_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>
#include <QTimer>
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
    db::Vehicle::Type decodeType(uint8_t type)
    {
        switch (type) //TODO: other vehicles
        {
        case MAV_TYPE_FIXED_WING: return db::Vehicle::FixedWing;
        case MAV_TYPE_TRICOPTER: return db::Vehicle::Tricopter;
        case MAV_TYPE_QUADROTOR: return db::Vehicle::Quadcopter;
        case MAV_TYPE_HEXAROTOR: return db::Vehicle::Hexcopter;
        case MAV_TYPE_OCTOROTOR: return db::Vehicle::Octocopter;
        case MAV_TYPE_COAXIAL: return db::Vehicle::Coaxial;
        case MAV_TYPE_HELICOPTER: return db::Vehicle::Helicopter;
        case MAV_TYPE_VTOL_DUOROTOR:
        case MAV_TYPE_VTOL_QUADROTOR:
        case MAV_TYPE_VTOL_TILTROTOR:
        case MAV_TYPE_VTOL_RESERVED2:
        case MAV_TYPE_VTOL_RESERVED3:
        case MAV_TYPE_VTOL_RESERVED4:
        case MAV_TYPE_VTOL_RESERVED5: return db::Vehicle::Vtol;
        case MAV_TYPE_AIRSHIP:
        case MAV_TYPE_FREE_BALLOON: return db::Vehicle::Airship;
        case MAV_TYPE_KITE: return db::Vehicle::Kite;
        case MAV_TYPE_FLAPPING_WING: return db::Vehicle::Ornithopter;
        case MAV_TYPE_GENERIC:
        default: return db::Vehicle::UnknownType;
        }
    }

    /*BaseVehicle::State decodeState(uint8_t state)
    {
        switch (state)
        {
        case MAV_STATE_BOOT:
            return BaseVehicle::Boot;
        case MAV_STATE_CALIBRATING:
            return BaseVehicle::Calibrating;
        case MAV_STATE_STANDBY:
            return BaseVehicle::Standby;
        case MAV_STATE_ACTIVE:
            return BaseVehicle::Active;
        case MAV_STATE_CRITICAL:
            return BaseVehicle::Critical;
        case MAV_STATE_EMERGENCY:
            return BaseVehicle::Emergency;
        case MAV_STATE_UNINIT:
        default:
            return BaseVehicle::UnknownState;
        }
    }*/
}

HeartbeatHandler::HeartbeatHandler(db::DbFacade* dbFacade, TelemetryService* telemetryService,
                                   MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_dbFacade(dbFacade),
    m_telemetryService(telemetryService),
    m_timer(new QTimer(this))
{
    QObject::connect(m_timer, &QTimer::timeout, this, &HeartbeatHandler::sendHeartbeat);
    m_timer->start(1000); //TODO: heartbeat emit disabling and freqency selecting
}

HeartbeatHandler::~HeartbeatHandler()
{
    delete m_timer;
}

void HeartbeatHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_HEARTBEAT) return;

    mavlink_heartbeat_t heartbeat;
    mavlink_msg_heartbeat_decode(&message, &heartbeat);

    db::VehiclePtr vehicle =  m_dbFacade->vehicle(
                                  m_dbFacade->vehicleIdByMavId(message.sysid));

    if (!vehicle && settings::Provider::value(settings::communication::autoAdd).toBool())
    {
        vehicle = db::VehiclePtr::create();
        vehicle->setMavId(message.sysid);
        vehicle->setType(db::Vehicle::Auto);
        vehicle->setName(tr("Added vehicle"));
        m_dbFacade->save(vehicle);
    }

    if (vehicle && vehicle->type() == db::Vehicle::Auto)
    {
        vehicle->setType(::decodeType(heartbeat.type));
    }

    Telemetry* node = m_telemetryService->mavNode(message.sysid);
    if (!node) return;

    // TODO: online timer
    node->setParameter({ Telemetry::Status, Telemetry::Online }, true);
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
                       decodeCustomMode(heartbeat.autopilot,
                                        heartbeat.type,
                                        heartbeat.custom_mode));
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
