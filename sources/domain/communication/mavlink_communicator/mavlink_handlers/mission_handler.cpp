#include "mission_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mavlink_communicator.h"

#include "mission_service.h"
#include "mission.h"

using namespace domain;

namespace
{
    MissionItem::Command decodeCommand(uint16_t command)
    {
        switch (command) {
        case MAV_CMD_NAV_TAKEOFF: return MissionItem::Takeoff;
        case MAV_CMD_NAV_WAYPOINT: return MissionItem::Waypoint;
        case MAV_CMD_NAV_LOITER_UNLIM:
        case MAV_CMD_NAV_LOITER_TURNS:
            return MissionItem::Loiter;
        case MAV_CMD_NAV_RETURN_TO_LAUNCH: return MissionItem::Return;
        case MAV_CMD_NAV_LAND: return MissionItem::Landing;
        default: return MissionItem::UnknownCommand;
        }
    }
}

MissionHandler::MissionHandler(MissionService* missionService,
                               MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_missionService(missionService)
{
    connect(missionService, &MissionService::commandRequestMission,
            this, &MissionHandler::requestMission);
}

void MissionHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid == MAVLINK_MSG_ID_MISSION_COUNT)
    {
        Mission* mission = m_missionService->requestMissionForVehicle(message.sysid);

        mavlink_mission_count_t missionCount;
        mavlink_msg_mission_count_decode(&message, &missionCount);

        mission->setCount(missionCount.count);
        // TODO: request by timer
        for (uint16_t seq = 0; seq < missionCount.count; ++seq)
        {
            this->requestMissionItem(message.sysid, seq);
        }
        return;
    }

    if (message.msgid == MAVLINK_MSG_ID_MISSION_ITEM)
    {
        Mission* mission = m_missionService->requestMissionForVehicle(message.sysid);

        mavlink_mission_item_t msgItem;
        mavlink_msg_mission_item_decode(&message, &msgItem);

        MissionItem* item = mission->requestItem(msgItem.seq);
        // TODO: coordinate system depends MAV_FRAME
        if (!qFuzzyIsNull(msgItem.x) || !qFuzzyIsNull(msgItem.y) ||
            !qFuzzyIsNull(msgItem.z))
        {
            item->setCoordinate(QGeoCoordinate(msgItem.x, msgItem.y, msgItem.z));
        }
        item->setCommand(::decodeCommand(msgItem.command));
        item->setCurrent(msgItem.current);

        return;
    }

    if (message.msgid == MAVLINK_MSG_ID_MISSION_ACK)
    {
        Mission* mission = m_missionService->requestMissionForVehicle(message.sysid);

        mavlink_mission_ack_t missionAck;
        mavlink_msg_mission_ack_decode(&message, &missionAck);

        // TODO: handle missionAck
    }
}

void MissionHandler::requestMission(uint8_t id)
{
    mavlink_message_t message;
    mavlink_mission_request_list_t request;

    // TODO: request Timer

    request.target_system = id;
    request.target_component = MAV_COMP_ID_MISSIONPLANNER;

    mavlink_msg_mission_request_list_encode(m_communicator->systemId(),
                                            m_communicator->componentId(),
                                            &message, &request);
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
