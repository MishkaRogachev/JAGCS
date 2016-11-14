#include "home_position_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "mavlink_communicator.h"

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

void HomePositionHandler::sendHomePositionRequest()
{
    //TODO: MAV_CMD_GET_HOME_POSITION
}

void HomePositionHandler::sendHomePositionSetting(
        const QGeoCoordinate& position, const QVector3D& approach)
{
    mavlink_message_t message;
    mavlink_set_home_position_t home;

    // TODO: mavlink helper
    home.latitude = position.latitude() * 1e7;
    home.longitude = position.latitude() * 1e7;
    home.altitude = position.altitude() * 1000;

    home.approach_x = approach.x();
    home.approach_y = approach.y();
    home.approach_z = approach.z();

    mavlink_msg_set_home_position_encode(m_communicator->systemId(),
                                         m_communicator->componentId(),
                                         &message, &home);

    m_communicator->sendMessageAllLinks(message);
}
