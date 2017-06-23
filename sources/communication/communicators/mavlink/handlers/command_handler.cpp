#include "command_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mavlink_communicator.h"

#include "command_service.h"
#include "command.h"

using namespace comm;
using namespace domain;

namespace
{
    uint16_t toMavlinkCommand(Command::CommandType type)
    {
        switch (type) {
        case Command::ArmDisarm: return MAV_CMD_COMPONENT_ARM_DISARM;
        case Command::Return: return MAV_CMD_NAV_RETURN_TO_LAUNCH;
        case Command::Start: return MAV_CMD_MISSION_START;
        case Command::Jump: return MAV_CMD_DO_JUMP;
        case Command::Idle:
        default: return 0;
        }
    }
}

CommandHandler::CommandHandler(CommandService* commandService,
                               MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_commandService(commandService)
{
    connect(commandService, &CommandService::gotCommand,
            this, &CommandHandler::onGotCommand);
}

void CommandHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message) // TODO: handle command quitantion
}

void CommandHandler::onGotCommand()
{
    while (m_commandService->hasCommand())
    {
        this->sendCommand(m_commandService->headCommand());
    }
}

void CommandHandler::sendCommand(const Command& command)
{
    mavlink_message_t message;
    mavlink_command_long_t mavCommand;

    // mavCommand.target_system = mavId; TODO: target command id
    mavCommand.target_component = 0;
    mavCommand.confirmation = 0;
    mavCommand.command = ::toMavlinkCommand(command.type());

    QVariantList args = command.arguments();
    if (args.count() > 0) mavCommand.param1 = args.at(0).toFloat();
    if (args.count() > 1) mavCommand.param2 = args.at(1).toFloat();
    if (args.count() > 2) mavCommand.param3 = args.at(2).toFloat();
    if (args.count() > 3) mavCommand.param4 = args.at(3).toFloat();
    if (args.count() > 4) mavCommand.param5 = args.at(4).toFloat();
    if (args.count() > 5) mavCommand.param6 = args.at(5).toFloat();
    if (args.count() > 6) mavCommand.param7 = args.at(6).toFloat();

    mavlink_msg_command_long_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &mavCommand);
    m_communicator->sendMessageAllLinks(message);
}
