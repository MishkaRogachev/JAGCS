#include "mission_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "db_facade.h"
#include "mission.h"
#include "mission_item.h"
#include "vehicle.h"
#include "mission_assignment.h"

#include "mavlink_communicator.h"

#include "command_service.h"
#include "mission_service.h"
#include "telemetry_service.h"
#include "telemetry.h"

namespace
{
    dao::MissionItem::Command decodeCommand(uint16_t command)
    {
        switch (command) {
        case MAV_CMD_NAV_TAKEOFF:
            return dao::MissionItem::Takeoff;
        case MAV_CMD_NAV_WAYPOINT:
            return dao::MissionItem::Waypoint;
        case MAV_CMD_NAV_LOITER_TO_ALT:
            return dao::MissionItem::LoiterAltitude;
        case MAV_CMD_NAV_LOITER_TURNS:
            return dao::MissionItem::LoiterTurns;
        case MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT:
            return dao::MissionItem::Continue;
        case MAV_CMD_NAV_RETURN_TO_LAUNCH:
            return dao::MissionItem::Return;
        case MAV_CMD_NAV_LAND:
            return dao::MissionItem::Landing;
        default:
            return dao::MissionItem::UnknownCommand;
        }
    }

    uint16_t encodeCommand(dao::MissionItem::Command command)
    {
        switch (command) {
        case dao::MissionItem::Takeoff:
            return MAV_CMD_NAV_TAKEOFF;
        case dao::MissionItem::Waypoint:
            return MAV_CMD_NAV_WAYPOINT;
        case dao::MissionItem::LoiterAltitude:
            return MAV_CMD_NAV_LOITER_TO_ALT;
        case dao::MissionItem::LoiterTurns:
            return MAV_CMD_NAV_LOITER_TURNS;
        case dao::MissionItem::Continue:
            return MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT;
        case dao::MissionItem::Return:
            return MAV_CMD_NAV_RETURN_TO_LAUNCH;
        case dao::MissionItem::Landing:
            return MAV_CMD_NAV_LAND;
        default:
            return 0;
        }
    }
}

using namespace comm;
using namespace domain;

MissionHandler::MissionHandler(db::DbFacade* dbFacade,
                               domain::TelemetryService* telemetryService,
                               MissionService* missionService,
                               domain::CommandService* commandService,
                               MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_dbFacade(dbFacade),
    m_telemetryService(telemetryService),
    m_missionService(missionService)
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
    case MAVLINK_MSG_ID_MISSION_ITEM_REACHED:
        this->processMissionReached(message);
        break;
    default:
        break;
    }
}

void MissionHandler::download(const dao::MissionAssignmentPtr& assignment)
{
    dao::VehiclePtr vehicle = m_dbFacade->vehicle(assignment->vehicleId());
    if (vehicle.isNull()) return;

    for (const dao::MissionItemPtr& item: m_missionService->missionItems(assignment->missionId()))
    {
        item->setStatus(dao::MissionItem::NotActual);
        m_missionService->missionItemChanged(item);
    }

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

void MissionHandler::upload(const dao::MissionAssignmentPtr& assignment)
{
    dao::VehiclePtr vehicle = m_dbFacade->vehicle(assignment->vehicleId());
    dao::MissionPtr mission = m_missionService->mission(assignment->missionId());
    if (vehicle.isNull() || mission.isNull()) return;

    for (const dao::MissionItemPtr& item: m_missionService->missionItems(assignment->missionId()))
    {
        item->setStatus(dao::MissionItem::Uploading);
        m_missionService->missionItemChanged(item);
    }

    // TODO: upload Timer

    mavlink_message_t message;
    mavlink_mission_count_t count;

    count.target_system = vehicle->mavId();
    count.target_component = MAV_COMP_ID_MISSIONPLANNER;
    count.count = mission->count() + 1;

    mavlink_msg_mission_count_encode(m_communicator->systemId(),
                                     m_communicator->componentId(),
                                     &message, &count);
    m_communicator->sendMessageAllLinks(message);
}

void MissionHandler::requestMissionItem(uint8_t mavId, uint16_t seq)
{
    mavlink_message_t message;
    mavlink_mission_request_t missionRequest;

    missionRequest.target_system = mavId;
    missionRequest.target_component = MAV_COMP_ID_MISSIONPLANNER;
    missionRequest.seq = seq;

    mavlink_msg_mission_request_encode(m_communicator->systemId(),
                                       m_communicator->componentId(),
                                       &message, &missionRequest);
    m_communicator->sendMessageAllLinks(message);
}

void MissionHandler::sendMissionItem(uint8_t mavId, uint16_t seq)
{
    int vehicleId = m_dbFacade->vehicleIdByMavId(mavId);
    dao::MissionAssignmentPtr assignment = m_missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_message_t message;
    mavlink_mission_item_t msgItem;

    msgItem.target_system = mavId;
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
        dao::MissionItemPtr item = m_missionService->missionItem(assignment->missionId(), seq);
        if (item.isNull()) return;

        msgItem.seq = seq;
        msgItem.autocontinue = seq < m_missionService->mission(assignment->missionId())->count();

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

        // TODO: wait ack
        item->setStatus(dao::MissionItem::Actual);
        m_missionService->missionItemChanged(item);
    }

    mavlink_msg_mission_item_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &msgItem);
    m_communicator->sendMessageAllLinks(message);
}

void MissionHandler::sendMissionAck(uint8_t mavId)
{
    mavlink_message_t message;
    mavlink_mission_ack_t ackItem;

    ackItem.target_system = mavId;
    ackItem.target_component = MAV_COMP_ID_MISSIONPLANNER;
    ackItem.type = MAV_MISSION_ACCEPTED;

    mavlink_msg_mission_ack_encode(m_communicator->systemId(),
                                   m_communicator->componentId(),
                                   &message, &ackItem);
    m_communicator->sendMessageAllLinks(message);
}

void MissionHandler::processMissionCount(const mavlink_message_t& message)
{
    int vehicleId = m_dbFacade->vehicleIdByMavId(message.sysid);
    dao::MissionAssignmentPtr assignment = m_missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    // TODO: check, we realy downloading

    mavlink_mission_count_t missionCount;
    mavlink_msg_mission_count_decode(&message, &missionCount);

    // Remove superfluous items
    for (const dao::MissionItemPtr& item:
         m_missionService->missionItems(assignment->missionId()))
    {
        if (item->sequence() > missionCount.count - 1) m_missionService->remove(item);
    }

    for (uint16_t seq = 0; seq < missionCount.count; ++seq)
    {
        this->requestMissionItem(message.sysid, seq);
    }
}

void MissionHandler::processMissionItem(const mavlink_message_t& message)
{
    int vehicleId = m_dbFacade->vehicleIdByMavId(message.sysid);
    dao::MissionAssignmentPtr assignment = m_missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_mission_item_t msgItem;
    mavlink_msg_mission_item_decode(&message, &msgItem);

    if (msgItem.seq == 0) return; // have no interes in home point

    dao::MissionItemPtr item = m_missionService->missionItem(assignment->missionId(),
                                                             msgItem.seq);
    if (item.isNull())
    {
        item = dao::MissionItemPtr::create();
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

    item->setStatus(dao::MissionItem::Actual);
    m_missionService->save(item);
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
    mavlink_mission_current_t current;
    mavlink_msg_mission_current_decode(&message, &current);

    Telemetry* node = m_telemetryService->mavNode(message.sysid);
    if (!node) return;

    node->setParameter({ Telemetry::Navigator, Telemetry::CurrentWaypoint }, current.seq);
}

void MissionHandler::processMissionReached(const mavlink_message_t& message)
{
    int vehicleId = m_dbFacade->vehicleIdByMavId(message.sysid);
    dao::MissionAssignmentPtr assignment = m_missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_mission_item_reached_t reached;
    mavlink_msg_mission_item_reached_decode(&message, &reached);

    dao::MissionItemPtr item = m_missionService->missionItem(assignment->missionId(), reached.seq);
    if (item) item->setReached(true);
    emit m_missionService->missionItemChanged(item);
}
