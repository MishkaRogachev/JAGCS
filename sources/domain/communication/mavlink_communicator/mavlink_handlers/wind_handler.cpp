#include "wind_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

using namespace domain;

WindHandler::WindHandler(VehicleService* vehicleService,
                         MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(vehicleService)
{}

void WindHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_WIND) return;

    Vehicle* vehicle = m_vehicleService->vehicleForId(message.sysid);
    if (!vehicle) return;

    mavlink_wind_t wind;
    mavlink_msg_wind_decode(&message, &wind);

    vehicle->setWind(Wind(wind.direction, wind.speed, wind.speed_z));
}
