#include "mission_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "mavlink_communicator.h"

#include "mission_service.h"
#include "vehicle_service.h"

#include "mission.h"
#include "mission_item.h"
#include "vehicle_description.h"
#include "mission_assignment.h"

namespace
{
    db::MissionItem::Command decodeCommand(uint16_t command)
    {
        switch (command) {
        case MAV_CMD_NAV_TAKEOFF:
            return db::MissionItem::Takeoff;
        case MAV_CMD_NAV_WAYPOINT:
            return db::MissionItem::Waypoint;
        case MAV_CMD_NAV_LOITER_TO_ALT:
            return db::MissionItem::LoiterAltitude;
        case MAV_CMD_NAV_LOITER_TURNS:
            return db::MissionItem::LoiterTurns;
        case MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT:
            return db::MissionItem::Continue;
        case MAV_CMD_NAV_RETURN_TO_LAUNCH:
            return db::MissionItem::Return;
        case MAV_CMD_NAV_LAND:
            return db::MissionItem::Landing;
        default:
            return db::MissionItem::UnknownCommand;
        }
    }

    uint16_t encodeCommand(db::MissionItem::Command command)
    {
        switch (command) {
        case db::MissionItem::Takeoff:
            return MAV_CMD_NAV_TAKEOFF;
        case db::MissionItem::Waypoint:
            return MAV_CMD_NAV_WAYPOINT;
        case db::MissionItem::LoiterAltitude:
            return MAV_CMD_NAV_LOITER_TO_ALT;
        case db::MissionItem::LoiterTurns:
            return MAV_CMD_NAV_LOITER_TURNS;
        case db::MissionItem::Continue:
            return MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT;
        case db::MissionItem::Return:
            return MAV_CMD_NAV_RETURN_TO_LAUNCH;
        case db::MissionItem::Landing:
            return MAV_CMD_NAV_LAND;
        default:
            return 0;
        }
    }
}

using namespace comm;

MissionHandler::MissionHandler(domain::MissionService* missionService,
                               domain::VehicleService* vehicleService,
                               MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_missionService(missionService),
    m_vehicleService(vehicleService)
{}

void MissionHandler::processMessage(const mavlink_message_t& message)
{
    switch (message.msgid) {
    case MAVLINK_MSG_ID_MISSION_COUNT:
        this->processMissionCount(message);
        break;
    case MAVLINK_MSG_ID_MISSION_ITEM:
        this->processMissionItem(message);
        break;
    case MAVLINK_MSG_ID_MISSION_REQUEST:
        this->processMissionRequest(message);
        break;
    case MAVLINK_MSG_ID_MISSION_ACK:
        this->processMissionAck(message);
        break;
    case MAVLINK_MSG_ID_MISSION_CURRENT:
        this->processMissionCurrent(message);
        break;
    default:
        break;
    }
}

void MissionHandler::processMissionCount(const mavlink_message_t& message)
{
    mavlink_mission_count_t missionCount;
    mavlink_msg_mission_count_decode(&message, &missionCount);

    for (uint16_t seq = 0; seq < missionCount.count; ++seq)
    {
        // TODO: this->requestMissionItem(message.sysid, seq);
    }
}

void MissionHandler::processMissionItem(const mavlink_message_t& message)
{
    db::VehicleDescriptionPtr vehicle = m_vehicleService->findDescriptionByMavId(message.sysid);
    if (vehicle.isNull()) return;
    db::MissionAssignmentPtr assignment = m_missionService->vehicleAssignment(vehicle);
    if (assignment.isNull() ||
        assignment->status() != db::MissionAssignment::Downloading) return;

    mavlink_mission_item_t msgItem;
    mavlink_msg_mission_item_decode(&message, &msgItem);

    db::MissionItemPtr item = m_missionService->missionItem(
                                  m_missionService->mission(assignment->missionId()),
                                  msgItem.seq);
    if (item.isNull())
    {
        item.create();
        item->setMissionId(assignment->missionId());
        item->setSequence(msgItem.seq);
    }

    item->setCommand(::decodeCommand(msgItem.command));

    switch (msgItem.frame)
    {
    case MAV_FRAME_GLOBAL_RELATIVE_ALT:
        item->setAltitudeRelative(true);
        break;
    case MAV_FRAME_GLOBAL:
    default:
        item->setAltitudeRelative(false);
        break;
    }

    item->setAltitude(msgItem.z);

    if (qFuzzyIsNull(msgItem.x) && qFuzzyIsNull(msgItem.y))
    {
        item->setLatitude(qQNaN());
        item->setLongitude(qQNaN());
    }
    else
    {
        item->setLatitude(msgItem.x);
        item->setLongitude(msgItem.y);
    }

    switch (msgItem.command)
    {
    case MAV_CMD_NAV_TAKEOFF:
        item->setPitch(msgItem.param1);
        break;
    case MAV_CMD_NAV_WAYPOINT:
    case MAV_CMD_NAV_LOITER_TO_ALT:
        item->setRadius(msgItem.param2);
        break;
    case MAV_CMD_NAV_LOITER_TURNS:
        item->setPeriods(msgItem.param1);
        item->setRadius(msgItem.param3);
        break;
    default:
        break;
    }
}

void MissionHandler::processMissionRequest(const mavlink_message_t& message)
{
    mavlink_mission_request_t request;
    mavlink_msg_mission_request_decode(&message, &request);

    // TODO: this->sendMissionItem(message.sysid, request.seq);
}

void MissionHandler::processMissionAck(const mavlink_message_t& message)
{
    mavlink_mission_ack_t missionAck;
    mavlink_msg_mission_ack_decode(&message, &missionAck);

    // TODO: handle missionAck.type
}

void MissionHandler::processMissionCurrent(const mavlink_message_t& message)
{
    mavlink_mission_current_t missionCurrent;
    mavlink_msg_mission_current_decode(&message, &missionCurrent);

    // TODO: handle missionCurrent.seq
}
