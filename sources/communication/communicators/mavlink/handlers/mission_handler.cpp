#include "mission_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "db_facade.h"
#include "mission.h"
#include "mission_item.h"
#include "vehicle_description.h"
#include "mission_assignment.h"

#include "mavlink_communicator.h"

#include "command_service.h"
#include "vehicle_service.h"

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

MissionHandler::MissionHandler(db::DbFacade* dbFacade,
                               domain::VehicleService* vehicleService,
                               domain::CommandService* commandService,
                               MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_dbFacade(dbFacade),
    m_vehicleService(vehicleService)
{
    connect(commandService, &domain::CommandService::download,
            this, &MissionHandler::download);
    connect(commandService, &domain::CommandService::upload,
            this, &MissionHandler::upload);
}

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

void MissionHandler::download(const db::MissionAssignmentPtr& assignment)
{
    db::VehicleDescriptionPtr vehicle = m_vehicleService->description(
                                            assignment->vehicleId());
    if (vehicle.isNull()) return;

    assignment->setStatus(db::MissionAssignment::Downloading);

    // TODO: request Timer

    mavlink_message_t message;
    mavlink_mission_request_list_t request;

    request.target_system = vehicle->mavId();
    request.target_component = MAV_COMP_ID_MISSIONPLANNER;

    mavlink_msg_mission_request_list_encode(m_communicator->systemId(),
                                            m_communicator->componentId(),
                                            &message, &request);
    m_communicator->sendMessageAllLinks(message);
}

void MissionHandler::upload(const db::MissionAssignmentPtr& assignment)
{
    db::VehicleDescriptionPtr vehicle = m_vehicleService->description(
                                            assignment->vehicleId());
    if (vehicle.isNull()) return;

    assignment->setStatus(db::MissionAssignment::Uploading);

    // TODO: upload Timer

    mavlink_message_t message;
    mavlink_mission_count_t count;

    count.target_system = vehicle->mavId();
    count.target_component = MAV_COMP_ID_MISSIONPLANNER;
    count.count = m_dbFacade->mission(assignment->missionId())->count();

//    TODO: assignment->setCurrentProgress(0);
//    assignment->setTotalProgress(count.count);

    mavlink_msg_mission_count_encode(m_communicator->systemId(),
                                     m_communicator->componentId(),
                                     &message, &count);
    m_communicator->sendMessageAllLinks(message);
}

void MissionHandler::requestMissionItem(uint8_t id, uint16_t seq)
{
    mavlink_message_t message;
    mavlink_mission_request_t missionRequest;

    missionRequest.target_system = id;
    missionRequest.target_component = MAV_COMP_ID_MISSIONPLANNER;
    missionRequest.seq = seq;

    mavlink_msg_mission_request_encode(m_communicator->systemId(),
                                       m_communicator->componentId(),
                                       &message, &missionRequest);
    m_communicator->sendMessageAllLinks(message);
}

void MissionHandler::sendMissionItem(uint8_t id, uint16_t seq)
{
    db::VehicleDescriptionPtr vehicle = m_vehicleService->findDescriptionByMavId(id);
    if (vehicle.isNull()) return;
    db::MissionAssignmentPtr assignment = m_dbFacade->vehicleAssignment(vehicle->id());
    if (assignment.isNull() ||
        assignment->status() != db::MissionAssignment::Uploading) return;

    mavlink_message_t message;
    mavlink_mission_item_t msgItem;

    msgItem.target_system = id;
    msgItem.target_component = MAV_COMP_ID_MISSIONPLANNER;

    if (seq == 0) // fake home point
    {
        msgItem.seq = 0;
        msgItem.autocontinue = true;
        msgItem.command = MAV_CMD_NAV_WAYPOINT;
        msgItem.frame = MAV_FRAME_GLOBAL;

        msgItem.x = 0;
        msgItem.y = 0;
        msgItem.z = 0;
    }
    else
    {
        db::MissionItemPtr item = m_dbFacade->missionItem(assignment->missionId(), seq);
        if (item.isNull()) return;

        msgItem.seq = seq;
        msgItem.autocontinue = seq < m_dbFacade->mission(assignment->missionId())->count();

        msgItem.command = ::encodeCommand(item->command());

        if (!qIsNaN(item->altitude()))
        {
            msgItem.frame = item->isAltitudeRelative() ?
                                MAV_FRAME_GLOBAL_RELATIVE_ALT : MAV_FRAME_GLOBAL;
            msgItem.z = item->altitude();
        }

        if (!qIsNaN(item->latitude()))
        {
            msgItem.x = item->latitude();
        }

        if (!qIsNaN(item->longitude()))
        {
            msgItem.y = item->longitude();
        }

        switch (msgItem.command)
        {
        case MAV_CMD_NAV_TAKEOFF:
            msgItem.param1 = item->pitch();
        case MAV_CMD_NAV_LAND:// TODO: abort altitude
            // TODO: yaw
            //msgItem.param4 = takeoffItem->yaw();
            break;
        case MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT:
            // TODO: climb
            //msgItem.param1 = item->climb() > 1 ? 1 : altitudeItem->climb() < 0 ? -1 : 0;
            break;
        case MAV_CMD_NAV_WAYPOINT:
        case MAV_CMD_NAV_LOITER_TO_ALT:
            msgItem.param2 = item->radius();
            break;
        case MAV_CMD_NAV_LOITER_TURNS:
            msgItem.param1 = item->periods();
            msgItem.param3 = item->radius();
            break;
        default:
            break;
        }
    }

    mavlink_msg_mission_item_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &msgItem);
    m_communicator->sendMessageAllLinks(message);
}

void MissionHandler::sendMissionAck(uint8_t id)
{
    mavlink_message_t message;
    mavlink_mission_ack_t ackItem;

    ackItem.target_system = id;
    ackItem.target_component = MAV_COMP_ID_MISSIONPLANNER;
    ackItem.type = MAV_MISSION_ACCEPTED;

    mavlink_msg_mission_ack_encode(m_communicator->systemId(),
                                   m_communicator->componentId(),
                                   &message, &ackItem);
    m_communicator->sendMessageAllLinks(message);
}

void MissionHandler::processMissionCount(const mavlink_message_t& message)
{
    mavlink_mission_count_t missionCount;
    mavlink_msg_mission_count_decode(&message, &missionCount);

    for (uint16_t seq = 0; seq < missionCount.count; ++seq)
    {
        this->requestMissionItem(message.sysid, seq);
    }
}

void MissionHandler::processMissionItem(const mavlink_message_t& message)
{
    db::VehicleDescriptionPtr vehicle = m_vehicleService->findDescriptionByMavId(message.sysid);
    if (vehicle.isNull()) return;
    db::MissionAssignmentPtr assignment = m_dbFacade->vehicleAssignment(vehicle->id());
    if (assignment.isNull() ||
        assignment->status() != db::MissionAssignment::Downloading) return;

    mavlink_mission_item_t msgItem;
    mavlink_msg_mission_item_decode(&message, &msgItem);

    if (msgItem.seq == 0) return; // have no interes in home point

    db::MissionItemPtr item = m_dbFacade->missionItem(assignment->missionId(),
                                                      msgItem.seq);
    if (item.isNull())
    {
        item = db::MissionItemPtr::create();
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

    m_dbFacade->save(item);
}

void MissionHandler::processMissionRequest(const mavlink_message_t& message)
{
    mavlink_mission_request_t request;
    mavlink_msg_mission_request_decode(&message, &request);

    this->sendMissionItem(message.sysid, request.seq);
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
