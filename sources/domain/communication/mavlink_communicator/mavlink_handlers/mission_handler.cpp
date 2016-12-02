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

MissionHandler::MissionHandler(MissionService* missionService,
                               MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_missionService(missionService)
{}

void MissionHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid == MAVLINK_MSG_ID_MISSION_COUNT)
    {
        Mission* mission = m_missionService->requestMission(message.sysid);

        mavlink_mission_count_t missionCount;
        mavlink_msg_mission_count_decode(&message, &missionCount);

        qDebug() << message.sysid << missionCount.target_system;

        mission->setCount(missionCount.count);
        return;
    }

    if (message.msgid == MAVLINK_MSG_ID_MISSION_ITEM)
    {
        Mission* mission = m_missionService->requestMission(message.sysid);

        mavlink_mission_item_t itemMsg;
        mavlink_msg_mission_item_decode(&message, &itemMsg);

        MissionItem* item = mission->requestItem(itemMsg.seq);
        // TODO: coordinate system depends MAV_FRAME
        item->setCoordinate(QGeoCoordinate(itemMsg.x, itemMsg.y, itemMsg.z));
        item->setCurrent(itemMsg.current);
        // TODO: MAV_CMD

        return;
    }

    if (message.msgid == MAVLINK_MSG_ID_MISSION_ACK)
    {
        Mission* mission = m_missionService->requestMission(message.sysid);

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

void MissionHandler::requestMissionItem(uint8_t id, uint16_t item)
{
    mavlink_message_t message;
    mavlink_mission_request_t missionRequest;

    missionRequest.target_system = id;
    missionRequest.target_component = MAV_COMP_ID_MISSIONPLANNER;
    missionRequest.seq = item;

    mavlink_msg_mission_request_encode(m_communicator->systemId(),
                                       m_communicator->componentId(),
                                       &message, &missionRequest);
    m_communicator->sendMessageAllLinks(message);
}
