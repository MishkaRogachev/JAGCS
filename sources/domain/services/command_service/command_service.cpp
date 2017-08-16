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
}

CommandSender* CommandService::sender() const
{
    return m_sender;
}

void CommandService::executeCommand(const Command& command)
{
    m_sender->addCommand(command);
}

void CommandService::rejectCommand(Command::CommandType& type)
{
    m_sender->removeCommand(type);
}
