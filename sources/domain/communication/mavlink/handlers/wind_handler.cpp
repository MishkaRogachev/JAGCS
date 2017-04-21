#include "wind_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "vehicle_service.h"
#include "aerial_vehicle.h"

using namespace domain;

WindHandler::WindHandler(VehicleService* vehicleService,
                         data_source::MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(vehicleService)
{}

void WindHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_WIND) return;

    AerialVehicle* vehicle = m_vehicleService->aerialVehicle(message.sysid);
    if (!vehicle) return;

    mavlink_wind_t wind;
    mavlink_msg_wind_decode(&message, &wind);

    vehicle->setWind(Wind(wind.direction, wind.speed, wind.speed_z));
}
