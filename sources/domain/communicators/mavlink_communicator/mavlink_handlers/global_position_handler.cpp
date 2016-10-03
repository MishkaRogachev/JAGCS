#include "global_position_handler.h"

// MAVLink
#include <mavlink.h>
#include <mavlink_msg_global_position_int_cov.h>

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

using namespace domain;

GlobalPositionHandler::GlobalPositionHandler(VehicleService* vehicleService,
                                             QObject* parent):
    AbstractMavLinkHandler(parent),
    m_vehicleService(vehicleService)
{}

void GlobalPositionHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_GLOBAL_POSITION_INT_COV ||
        message.sysid == 0) return;

    Vehicle* vehicle = m_vehicleService->requestVehicle(message.sysid);

    mavlink_global_position_int_cov_t position;
    mavlink_msg_global_position_int_cov_decode(&message, &position);

    vehicle->setNavigation(Navigation(
                               QGeoCoordinate(
                                   double(position.lat / 1e7),
                                   double(position.lon / 1e7),
                                   double(position.alt / 1000)),
                               QVector3D(
                                   position.vx, position.vy, position.vz)));
}
