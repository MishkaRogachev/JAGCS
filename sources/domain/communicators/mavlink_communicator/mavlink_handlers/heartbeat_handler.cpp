#include "heartbeat_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QTimer>

// Internal
#include "mavlink_communicator.h"
#include "vehicle_service.h"
#include "vehicle.h"

using namespace domain;

namespace
{
    Vehicle::Type vehicleTypeFromMavType(uint8_t type)
    {
        switch (type) //TODO: other vehicles
        {
        case MAV_TYPE_FIXED_WING:
            return Vehicle::FixedWingAircraft;
        case MAV_TYPE_GENERIC:
        default:
            return Vehicle::UnknownType;
        }
    }

    Vehicle::State vehicleStateFromMavState(uint8_t state)
    {
        switch (state)
        {
        case MAV_STATE_BOOT:
            return Vehicle::Boot;
        case MAV_STATE_CALIBRATING:
            return Vehicle::Calibrating;
        case MAV_STATE_STANDBY:
            return Vehicle::Standby;
        case MAV_STATE_ACTIVE:
            return Vehicle::Active;
        case MAV_STATE_CRITICAL:
            return Vehicle::Critical;
        case MAV_STATE_EMERGENCY:
            return Vehicle::Emergency;
        case MAV_STATE_UNINIT:
        default:
            return Vehicle::UnknownState;
        }
    }

    bool hasMavModeFlag(uint8_t mode, MAV_MODE_FLAG flag)
    {
        return (mode & flag);
    }
}

HeartbeatHandler::HeartbeatHandler(VehicleService* vehicleService,
                                   MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(),
    m_vehicleService(vehicleService),
    m_communicator(communicator),
    m_timer(new QTimer())
{
    QObject::connect(m_timer, &QTimer::timeout, m_timer,
                     [this]() { this->sendHeartbeat(); });
    m_timer->start(1000); //TODO: heartbeat emit disabling and freqency selecting
}

HeartbeatHandler::~HeartbeatHandler()
{
    delete m_timer;
}

void HeartbeatHandler::sendHeartbeat()
{
    mavlink_message_t message;
    mavlink_heartbeat_t heartbeat;
    heartbeat.type = MAV_TYPE_GCS;
    mavlink_msg_heartbeat_encode(m_communicator->systemId(),
                                 m_communicator->componentId(),
                                 &message, &heartbeat);
    m_communicator->sendMessage(message);
}

int HeartbeatHandler::messageId() const
{
    return MAVLINK_MSG_ID_HEARTBEAT;
}

void HeartbeatHandler::processMessage(const mavlink_message_t& message)
{
    if (message.sysid == 0) return;
    Vehicle* vehicle = m_vehicleService->requestVehicle(message.sysid);

    mavlink_heartbeat_t heartbeat;
    mavlink_msg_heartbeat_decode(&message, &heartbeat);

    vehicle->setType(::vehicleTypeFromMavType(heartbeat.type));
    vehicle->setState(::vehicleStateFromMavState(heartbeat.system_status));
    vehicle->setAutonomous(::hasMavModeFlag(heartbeat.base_mode, MAV_MODE_FLAG_AUTO_ENABLED));
    //TODO: handle another MAV_MODE_FLAG flags
}
