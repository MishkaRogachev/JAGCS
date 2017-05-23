#include "command_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mavlink_communicator.h"

#include "command_service.h"

using namespace comm;
using namespace domain;

CommandHandler::CommandHandler(CommandService* commandService,
                               MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_commandService(commandService)
{
    // TODO: connect commandService
}

void CommandHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message) // TODO: handle command quitantion
}

void CommandHandler::sendArmDisarm(int mavId, bool arm)
{
    mavlink_message_t message;
    mavlink_command_long_t command;

    command.target_system = mavId;
    command.target_component = 0;
    command.confirmation = 0;
    command.command = MAV_CMD_COMPONENT_ARM_DISARM;
    command.param1 = arm;

    mavlink_msg_command_long_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &command);
    m_communicator->sendMessageAllLinks(message);
}

void CommandHandler::sendReturn(int mavId)
{
    mavlink_message_t message;
    mavlink_command_long_t command;

    command.target_system = mavId;
    command.target_component = 0;
    command.confirmation = 0;
    command.command = MAV_CMD_NAV_RETURN_TO_LAUNCH;

    mavlink_msg_command_long_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &command);
    m_communicator->sendMessageAllLinks(message);
}

void CommandHandler::sendMissionRestart(int mavId)
{
    this->sendMissionStart(mavId, 1);
}

void CommandHandler::sendMissionStart(int mavId, int startPoint)
{
    mavlink_message_t message;
    mavlink_command_long_t command;

    command.target_system = mavId;
    command.target_component = 0;
    command.confirmation = 0;
    command.command = MAV_CMD_MISSION_START;
    command.param1 = startPoint;
    //TODO: command.param2 = vehicle->missionItems() - 1;

    mavlink_msg_command_long_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &command);
    m_communicator->sendMessageAllLinks(message);
}

void CommandHandler::sendMissionJumpTo(int mavId, int startPoint)
{
    mavlink_message_t message;
    mavlink_command_long_t command;

    command.target_system = mavId;
    command.target_component = 0;
    command.confirmation = 0;
    command.command = MAV_CMD_DO_JUMP;
    command.param1 = startPoint;

    mavlink_msg_command_long_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &command);
    m_communicator->sendMessageAllLinks(message);
}
