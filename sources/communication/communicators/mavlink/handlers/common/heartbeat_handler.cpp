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

#include "service_registry.h"

#include "vehicle_service.h"
#include "vehicle.h"

#include "telemetry_service.h"
#include "telemetry_portion.h"

#include "vehicle_types.h"

#include "notification_bus.h"

#include "mavlink_communicator.h"

using namespace comm;
using namespace domain;

namespace
{
    dto::Vehicle::Type decodeType(quint8 type)
    {
        switch (type) //TODO: other vehicles
        {
        case MAV_TYPE_FIXED_WING: return dto::Vehicle::FixedWing;
        case MAV_TYPE_TRICOPTER: return dto::Vehicle::Tricopter;
        case MAV_TYPE_QUADROTOR: return dto::Vehicle::Quadcopter;
        case MAV_TYPE_HEXAROTOR: return dto::Vehicle::Hexcopter;
        case MAV_TYPE_OCTOROTOR: return dto::Vehicle::Octocopter;
        case MAV_TYPE_COAXIAL: return dto::Vehicle::Coaxial;
        case MAV_TYPE_HELICOPTER: return dto::Vehicle::Helicopter;
        case MAV_TYPE_VTOL_DUOROTOR:
        case MAV_TYPE_VTOL_QUADROTOR:
        case MAV_TYPE_VTOL_TILTROTOR:
        case MAV_TYPE_VTOL_RESERVED2:
        case MAV_TYPE_VTOL_RESERVED3:
        case MAV_TYPE_VTOL_RESERVED4:
        case MAV_TYPE_VTOL_RESERVED5: return dto::Vehicle::Vtol;
        case MAV_TYPE_AIRSHIP:
        case MAV_TYPE_FREE_BALLOON: return dto::Vehicle::Airship;
        case MAV_TYPE_KITE: return dto::Vehicle::Kite;
        case MAV_TYPE_FLAPPING_WING: return dto::Vehicle::Ornithopter;
        case MAV_TYPE_GENERIC:
        default: return dto::Vehicle::UnknownType;
        }
    }

    domain::vehicle::SystemState decodeState(quint8 state)
    {
        switch (state)
        {
        case MAV_STATE_BOOT:
            return domain::vehicle::SystemState::Boot;
        case MAV_STATE_CALIBRATING:
            return domain::vehicle::SystemState::Calibrating;
        case MAV_STATE_STANDBY:
            return domain::vehicle::SystemState::Standby;
        case MAV_STATE_ACTIVE:
            return domain::vehicle::SystemState::Active;
        case MAV_STATE_CRITICAL:
            return domain::vehicle::SystemState::Critical;
        case MAV_STATE_EMERGENCY:
            return domain::vehicle::SystemState::Emergency;
        case MAV_STATE_UNINIT:
        default:
            return domain::vehicle::SystemState::UnknownState;
        }
    }
}

class HeartbeatHandler::Impl
{
public:
    VehicleService* vehicleService = serviceRegistry->vehicleService();
    TelemetryService* telemetryService = serviceRegistry->telemetryService();

    int sendTimer;

    QMap<int, QBasicTimer*> vehicleTimers;
};

HeartbeatHandler::HeartbeatHandler(MavLinkCommunicator* communicator):
    QObject(communicator),
    AbstractMavLinkHandler(communicator),
    d(new Impl())
{
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

    if (message.sysid == m_communicator->systemId() || message.sysid == 0) return;

    int vehicleId = d->vehicleService->vehicleIdByMavId(message.sysid);

    dto::VehiclePtr vehicle = d->vehicleService->vehicle(vehicleId);

    if (!vehicle && settings::Provider::value(settings::communication::autoAdd).toBool())
    {
        vehicle = dto::VehiclePtr::create();
        vehicle->setMavId(message.sysid);
        vehicle->setType(dto::Vehicle::Auto);
        vehicle->setName(tr("MAV %1").arg(message.sysid));
        d->vehicleService->save(vehicle);
    }

    if (vehicle)
    {
        bool changed  = false;

        if (!vehicle->isOnline())
        {
            vehicle->setOnline(true);
            changed = true;
            notificationBus->notify(tr("Vehicle %1").arg(vehicle->name()), tr("Online"),
                                 dto::Notification::Positive);
        }

        if (!d->vehicleTimers.contains(vehicleId))
        {
            d->vehicleTimers[vehicleId] = new QBasicTimer();
        }
        d->vehicleTimers[vehicleId]->start(
                    settings::Provider::value(settings::communication::timeout).toInt(),
                    this);

        if (vehicle->type() == dto::Vehicle::Auto)
        {
            vehicle->setType(::decodeType(heartbeat.type));
            changed = true;
        }
        if (changed) d->vehicleService->save(vehicle);
    }

    TelemetryPortion portion(d->telemetryService->mavNode(message.sysid));

    portion.setParameter({ Telemetry::System, Telemetry::Armed },
                         bool(heartbeat.base_mode & MAV_MODE_FLAG_DECODE_POSITION_SAFETY));
    portion.setParameter({ Telemetry::System, Telemetry::Auto },
                         bool(heartbeat.base_mode & MAV_MODE_FLAG_DECODE_POSITION_AUTO));
    portion.setParameter({ Telemetry::System, Telemetry::Guided },
                         bool(heartbeat.base_mode & MAV_MODE_FLAG_DECODE_POSITION_GUIDED));
    portion.setParameter({ Telemetry::System, Telemetry::Stabilized },
                         bool(heartbeat.base_mode & MAV_MODE_FLAG_DECODE_POSITION_STABILIZE));
    portion.setParameter({ Telemetry::System, Telemetry::Manual },
                         bool(heartbeat.base_mode & MAV_MODE_FLAG_DECODE_POSITION_MANUAL));
    portion.setParameter({ Telemetry::System, Telemetry::State },
                         QVariant::fromValue(::decodeState(heartbeat.system_status)));
}

void HeartbeatHandler::sendHeartbeat()
{
    mavlink_message_t message;
    mavlink_heartbeat_t heartbeat;

    heartbeat.type = MAV_TYPE_GCS;

    for (AbstractLink* link: m_communicator->links())
    {
        mavlink_msg_heartbeat_encode_chan(m_communicator->systemId(),
                                          m_communicator->componentId(),
                                          m_communicator->linkChannel(link),
                                          &message, &heartbeat);

        m_communicator->sendMessage(message, link);
    }
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

            dto::VehiclePtr vehicle = d->vehicleService->vehicle(d->vehicleTimers.key(timer));
            if (vehicle.isNull())
            {
                delete timer;
                d->vehicleTimers.remove(d->vehicleTimers.key(timer));
                return;
            }

            timer->stop();
            vehicle->setOnline(false);
            d->vehicleService->save(vehicle);

            notificationBus->notify(tr("Vehicle %1").arg(vehicle->name()), tr("Offline"),
                                 dto::Notification::Critical);
        }
    }
}
