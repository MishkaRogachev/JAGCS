#include "global_position_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

#include "mavlink_protocol_helpers.h"

using namespace domain;

GlobalPositionHandler::GlobalPositionHandler(VehicleService* vehicleService,
                                             MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(vehicleService)
{}

void GlobalPositionHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_GLOBAL_POSITION_INT_COV) return;

    Vehicle* vehicle = m_vehicleService->requestVehicle(message.sysid);

    mavlink_global_position_int_cov_t position;
    mavlink_msg_global_position_int_cov_decode(&message, &position);

    vehicle->setNavigation(Navigation(
                               QGeoCoordinate(
                                   decodeLatLon(position.lat),
                                   decodeLatLon(position.lon),
                                   decodeAltitude(position.alt)),
                               QVector3D(
                                   position.vx, position.vy, position.vz)));
}
