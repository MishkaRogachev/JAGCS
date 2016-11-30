#include "waypoint_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

using namespace domain;

WaypointHandler::WaypointHandler(VehicleService* vehicleService,
                                 MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(vehicleService)
{}

// http://qgroundcontrol.org/mavlink/waypoint_protocol
void WaypointHandler::processMessage(const mavlink_message_t& message)
{
    // TODO: WAYPOINT_COUNT, WAYPOINT, WAYPOINT_ACK
}

void WaypointHandler::requestList(uint8_t id)
{
    // TODO: MAVLINK_WAYPOINT_REQUEST_LIST
}

void WaypointHandler::requestWaypoint(uint8_t id, uint8_t waypoint)
{
    // TODO: WAYPOINT_REQUEST
}
