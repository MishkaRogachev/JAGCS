#include "home_position_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QVector3D>
#include <QVariant>
#include <QDebug>

// Internal
#include "mission_assignment.h"
#include "mission_item.h"

#include "mavlink_communicator.h"
#include "mavlink_protocol_helpers.h"

#include "service_registry.h"
#include "vehicle_service.h"
#include "mission_service.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

using namespace comm;
using namespace domain;

HomePositionHandler::HomePositionHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator)
{}

void HomePositionHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_HOME_POSITION) return;

    TelemetryPortion port(ServiceRegistry::telemetryService()->mavNode(message.sysid));

    mavlink_home_position_t home;
    mavlink_msg_home_position_decode(&message, &home);

    QGeoCoordinate coordinate(decodeLatLon(home.latitude), decodeLatLon(home.longitude),
                              decodeAltitude(home.altitude));
    QVector3D direction(home.approach_x, home.approach_y, home.approach_z);

    port.setParameter({ Telemetry::HomePosition, Telemetry::Coordinate },
                       QVariant::fromValue(coordinate));
    port.setParameter({ Telemetry::HomePosition, Telemetry::Direction },
                       QVariant::fromValue(direction));
    port.setParameter({ Telemetry::HomePosition, Telemetry::Altitude },
                       coordinate.altitude());

    int vehicleId = ServiceRegistry::vehicleService()->vehicleIdByMavId(message.sysid);
    dao::MissionAssignmentPtr assignment = ServiceRegistry::missionService()->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    dao::MissionItemPtr item = ServiceRegistry::missionService()->missionItem(assignment->missionId(), 0);
    if (item.isNull()) return;

    item->setLatitude(coordinate.latitude());
    item->setLongitude(coordinate.longitude());
    item->setAltitude(coordinate.altitude());
    item->setStatus(dao::MissionItem::Actual);

    ServiceRegistry::missionService()->missionItemChanged(item);

}

void HomePositionHandler::sendHomePositionRequest(quint8 mavId)
{
    mavlink_message_t message;
    mavlink_command_long_t command;

     command.target_system = mavId;
     command.target_component = 0;
     command.confirmation = 0;

     command.command = MAV_CMD_GET_HOME_POSITION;

     AbstractLink* link = m_communicator->mavSystemLink(mavId);
     if (!link) return;

     mavlink_msg_command_long_encode_chan(m_communicator->systemId(),
                                          m_communicator->componentId(),
                                          m_communicator->linkChannel(link),
                                          &message, &command);
     m_communicator->sendMessage(message, link);
}
