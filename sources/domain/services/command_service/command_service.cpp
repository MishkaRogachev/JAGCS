#include "command_service.h"

// Qt
#include <QQueue>

// Internal
#include "command_sender.h"

using namespace domain;

CommandService::CommandService(QObject* parent):
    QObject(parent),
    m_sender(new CommandSender(this))
{
    qRegisterMetaType<Command>("Command");
    qRegisterMetaType<Command::CommandType>("Command::CommandType");
    qRegisterMetaType<Command::CommandStatus>("Command::CommandStatus");

    connect(m_sender, &CommandSender::commandStatusChanged,
            this, &CommandService::commandStatusChanged);
}

CommandSender* CommandService::sender() const
{
    return m_sender;
}

void CommandService::executeCommand(const Command& command)
{
    if (command.type() == Command::UnknownCommand)
    {
        emit commandStatusChanged(Command::UnknownCommand, Command::Rejected);
        return;
    }

    m_sender->addCommand(command);
}

void CommandService::rejectCommand(Command::CommandType type)
{
    m_sender->removeCommand(type);

    emit commandStatusChanged(type, Command::Canceled);
}
