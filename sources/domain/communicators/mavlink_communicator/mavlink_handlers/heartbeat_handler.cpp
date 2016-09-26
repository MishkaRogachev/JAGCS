#include "heartbeat_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

using namespace domain;

namespace
{
    Vehicle::Type vehicleTypeFromMavType(uint8_t type)
    {
        switch (type)
        {
        case MAV_TYPE_FIXED_WING:
            return Vehicle::FixedWingAircraft;
        case MAV_TYPE_GENERIC:
        default:
            return Vehicle::UnknownType;
        }
    }
}


HeartbeatHandler::HeartbeatHandler(VehicleService* vehicleService):
    AbstractMavLinkHandler(),
    m_vehicleService(vehicleService)
{}

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
    //TODO: handle MAV_MODE_FLAG
    //TODO: handle MAV_STATE
}
