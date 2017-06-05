#include "home_position_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QVector3D>
#include <QVariant>
#include <QDebug>

// Internal
#include "mavlink_communicator.h"
#include "mavlink_protocol_helpers.h"

#include "telemetry.h"

using namespace comm;
using namespace domain;

HomePositionHandler::HomePositionHandler(TelemetryService* telemetryService,
                                         MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(telemetryService)
{
    // TODO: requestig timer for home position
}

void HomePositionHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_HOME_POSITION) return;

    TelemetryNode* node = m_telemetryService->nodeByMavId(message.sysid);
    if (!node) return;

    mavlink_home_position_t home;
    mavlink_msg_home_position_decode(&message, &home);

    QGeoCoordinate coordinate(decodeLatLon(home.latitude), decodeLatLon(home.longitude),
                              decodeAltitude(home.altitude));
    QVector3D direction(home.approach_x, home.approach_y, home.approach_z);

    node->setParameter({ telemetry::home, telemetry::coordinate }, QVariant::fromValue(coordinate));
    node->setParameter({ telemetry::home, telemetry::direction }, QVariant::fromValue(direction));

    node->notify();
}

void HomePositionHandler::sendHomePositionRequest(uint8_t mavId)
{
    mavlink_message_t message;
     mavlink_command_long_t command;

     command.target_system = mavId;
     command.target_component = 0;
     command.confirmation = 0;

     command.command = MAV_CMD_GET_HOME_POSITION;

     mavlink_msg_command_long_encode(m_communicator->systemId(),
                                     m_communicator->componentId(),
                                     &message, &command);
     m_communicator->sendMessageAllLinks(message);
}

/*
void HomePositionHandler::sendHomePositionSetting(uint8_t mavId, const Position& position)
{
    mavlink_message_t message;
    mavlink_set_home_position_t home;

    home.target_system = mavId;

    home.latitude = encodeLatLon(position.coordinate().latitude());
    home.longitude = encodeLatLon(position.coordinate().longitude());
    home.altitude = encodeAltitude(position.coordinate().altitude());

    home.approach_x = position.vector().x();
    home.approach_y = position.vector().y();
    home.approach_z = position.vector().z();

    mavlink_msg_set_home_position_encode(m_communicator->systemId(),
                                         m_communicator->componentId(),
                                         &message, &home);

    m_communicator->sendMessageAllLinks(message);
}
*/
