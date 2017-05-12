#include "mission_handler.h"

using namespace comm;

MissionHandler::MissionHandler(domain::MissionService* missionService,
                               MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_missionService(missionService)
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

}

void MissionHandler::processMissionItem(const mavlink_message_t& message)
{

}

void MissionHandler::processMissionRequest(const mavlink_message_t& message)
{

}

void MissionHandler::processMissionAck(const mavlink_message_t& message)
{

}

void MissionHandler::processMissionCurrent(const mavlink_message_t& message)
{

}
