#include "home_position_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

using namespace domain;

HomePositionHandler::HomePositionHandler(VehicleService* vehicleService,
                                         MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(vehicleService)
{}

void HomePositionHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_HOME_POSITION ||
        message.sysid == 0) return;

    Vehicle* vehicle = m_vehicleService->requestVehicle(message.sysid);

    mavlink_home_position_t home;
    mavlink_msg_home_position_decode(&message, &home);

    vehicle->setHomePosition(QGeoCoordinate(home.latitude / 1e7,
                                            home.longitude / 1e7,
                                            home.altitude / 1000));
    // TODO: approach
}
