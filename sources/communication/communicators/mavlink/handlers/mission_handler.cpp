#include "mission_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mission.h"
#include "mission_item.h"
#include "vehicle.h"
#include "mission_assignment.h"

#include "mavlink_communicator.h"

#include "service_registry.h"
#include "command_service.h"
#include "vehicle_service.h"
#include "mission_service.h"
#include "telemetry_service.h"
#include "telemetry.h"

namespace
{
    dao::MissionItem::Command decodeCommand(uint16_t command, quint8 seq)
    {
        switch (command) {
        case MAV_CMD_NAV_TAKEOFF:
            return dao::MissionItem::Takeoff;
        case MAV_CMD_NAV_WAYPOINT:
            return seq > 0 ? dao::MissionItem::Waypoint : dao::MissionItem::Home;
        case MAV_CMD_NAV_LOITER_UNLIM:
            return dao::MissionItem::LoiterUnlim;
        case MAV_CMD_NAV_LOITER_TO_ALT:
            return dao::MissionItem::LoiterAltitude;
        case MAV_CMD_NAV_LOITER_TURNS:
            return dao::MissionItem::LoiterTurns;
        case MAV_CMD_NAV_LOITER_TIME:
            return dao::MissionItem::LoiterTime;
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
        case dao::MissionItem::Home:
        case dao::MissionItem::Waypoint:
            return MAV_CMD_NAV_WAYPOINT;
        case dao::MissionItem::LoiterUnlim:
            return MAV_CMD_NAV_LOITER_UNLIM;
        case dao::MissionItem::LoiterAltitude:
            return MAV_CMD_NAV_LOITER_TO_ALT;
        case dao::MissionItem::LoiterTurns:
            return MAV_CMD_NAV_LOITER_TURNS;
        case dao::MissionItem::LoiterTime:
            return MAV_CMD_NAV_LOITER_TIME;
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

MissionHandler::MissionHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(ServiceRegistry::vehicleService()),
    m_telemetryService(ServiceRegistry::telemetryService()),
    m_missionService(ServiceRegistry::missionService())
{
    connect(m_missionService, &domain::MissionService::download, this, &MissionHandler::download);
    connect(m_missionService, &domain::MissionService::upload, this, &MissionHandler::upload);
    connect(m_missionService, &domain::MissionService::setCurrent, this, &MissionHandler::setCurrent);
}

void MissionHandler::processMessage(const mavlink_message_t& message)
{
    switch (message.msgid)
    {
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
    dao::VehiclePtr vehicle = m_vehicleService->vehicle(assignment->vehicleId());
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
    dao::VehiclePtr vehicle = m_vehicleService->vehicle(assignment->vehicleId());
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
    count.count = mission->count();

    mavlink_msg_mission_count_encode(m_communicator->systemId(),
                                     m_communicator->componentId(),
                                     &message, &count);
    m_communicator->sendMessageAllLinks(message);
}

void MissionHandler::setCurrent(int vehicleId, uint16_t seq)
{
    this->sendCurrentItem(m_vehicleService->mavIdByVehicleId(vehicleId), seq);
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
    int vehicleId = m_vehicleService->vehicleIdByMavId(mavId);
    dao::MissionAssignmentPtr assignment = m_missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_message_t message;
    mavlink_mission_item_t msgItem;

    msgItem.target_system = mavId;
    msgItem.target_component = MAV_COMP_ID_MISSIONPLANNER;

    dao::MissionItemPtr item = m_missionService->missionItem(assignment->missionId(), seq);
    if (item.isNull()) return;

    msgItem.seq = seq;
    msgItem.autocontinue = seq < m_missionService->mission(assignment->missionId())->count() - 1;

    msgItem.command = ::encodeCommand(item->command());

    if (!qIsNaN(item->altitude()))
    {
        msgItem.frame = item->isAltitudeRelative() ? MAV_FRAME_GLOBAL_RELATIVE_ALT : MAV_FRAME_GLOBAL;
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
    case MAV_CMD_NAV_LAND:
        msgItem.param1 = item->abortAltitude();
        msgItem.param4 = item->yaw();
        break;
    case MAV_CMD_NAV_WAYPOINT:
        msgItem.param2 = item->radius();
        break;
    case MAV_CMD_NAV_LOITER_UNLIM:
        msgItem.param3 = item->radius();
        break;
    case MAV_CMD_NAV_LOITER_TO_ALT:
        // TODO: heading required param1;
        msgItem.param2 = item->radius();
        break;
    case MAV_CMD_NAV_LOITER_TURNS:
        msgItem.param1 = item->repeats();
        msgItem.param3 = item->radius();
        break;
    case MAV_CMD_NAV_LOITER_TIME:
        msgItem.param1 = item->delay();
        msgItem.param3 = item->radius();
        break;
    case MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT:
        // FIXME: climb
        //msgItem.param1 = item->climb() > 1 ? 1 : altitudeItem->climb() < 0 ? -1 : 0;
        break;
    default:
        break;
    }

    // TODO: wait ack
    item->setStatus(dao::MissionItem::Actual);
    m_missionService->missionItemChanged(item);

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

void MissionHandler::sendCurrentItem(uint8_t mavId, uint16_t seq)
{
    mavlink_message_t message;
    mavlink_mission_set_current_t current;

    current.target_system = mavId;
    current.target_component = MAV_COMP_ID_MISSIONPLANNER;
    current.seq = seq;

    mavlink_msg_mission_set_current_encode(m_communicator->systemId(),
                                           m_communicator->componentId(),
                                           &message, &current);
    m_communicator->sendMessageAllLinks(message);
}

void MissionHandler::processMissionCount(const mavlink_message_t& message)
{
    int vehicleId = m_vehicleService->vehicleIdByMavId(message.sysid);
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
    int vehicleId = m_vehicleService->vehicleIdByMavId(message.sysid);
    dao::MissionAssignmentPtr assignment = m_missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_mission_item_t msgItem;
    mavlink_msg_mission_item_decode(&message, &msgItem);

    dao::MissionItemPtr item = m_missionService->missionItem(assignment->missionId(),
                                                             msgItem.seq);
    if (item.isNull())
    {
        item = dao::MissionItemPtr::create();
        item->setMissionId(assignment->missionId());
        item->setSequence(msgItem.seq);
    }

    item->setCommand(::decodeCommand(msgItem.command, msgItem.seq));

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
    case MAV_CMD_NAV_LAND:
        item->setAbortAltitude(msgItem.param1);
        item->setYaw(msgItem.param4);
        break;
    case MAV_CMD_NAV_WAYPOINT:
        item->setRadius(msgItem.param2);
        break;
    case MAV_CMD_NAV_LOITER_UNLIM:
        msgItem.param3 = item->radius();
        break;
    case MAV_CMD_NAV_LOITER_TO_ALT:
        // TODO: heading required param1;
        item->setRadius(msgItem.param2);
        break;
    case MAV_CMD_NAV_LOITER_TURNS:
        item->setRepeats(msgItem.param1);
        item->setRadius(msgItem.param3);
        break;
    case MAV_CMD_NAV_LOITER_TIME:
        item->setDelay(msgItem.param1);
        item->setRadius(msgItem.param3);
        break;
    case MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT:
        // ignore climb
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
    int vehicleId = m_vehicleService->vehicleIdByMavId(message.sysid);
    dao::MissionAssignmentPtr assignment = m_missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_mission_current_t current;
    mavlink_msg_mission_current_decode(&message, &current);

    for (const dao::MissionItemPtr& item: m_missionService->missionItems(assignment->missionId()))
    {
        if (item->isCurrent() != (item->sequence() == current.seq))
        {
            item->setCurrent(item->sequence() == current.seq);
            m_missionService->missionItemChanged(item);
        }
    }
}

void MissionHandler::processMissionReached(const mavlink_message_t& message)
{
    int vehicleId = m_vehicleService->vehicleIdByMavId(message.sysid);
    dao::MissionAssignmentPtr assignment = m_missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_mission_item_reached_t reached;
    mavlink_msg_mission_item_reached_decode(&message, &reached);

    dao::MissionItemPtr item = m_missionService->missionItem(assignment->missionId(), reached.seq);
    if (item)
    {
        item->setReached(true);
        emit m_missionService->missionItemChanged(item);
    }
}
