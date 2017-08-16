#include "command_sender.h"

// Qt
#include <QMap>
#include <QTimerEvent>

namespace
{
    const int interval = 500;
    const int maxAttemps = 5;
}

using namespace domain;

class CommandSender::Impl
{
public:
    QMap <Command::CommandType, Command> typeCommands;
    QMap <Command::CommandType, int> typeAttemps;
    QMap <Command::CommandType, int> typeTimers;
};

CommandSender::CommandSender(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

CommandSender::~CommandSender()
{}

void CommandSender::addCommand(const Command& command)
{
    if (d->typeTimers.contains(command.type())) this->killTimer(d->typeTimers.take(command.type()));

    d->typeCommands[command.type()] = command;
    d->typeAttemps[command.type()] = 0;

    emit sendCommand(command, d->typeAttemps[command.type()]);
    d->typeTimers[command.type()] = this->startTimer(::interval);
    emit commandStatusChanged(command.type(), Command::Sending);
}

void CommandSender::removeCommand(Command::CommandType type)
{
    d->typeCommands.remove(type);
    d->typeAttemps.remove(type);

    if (d->typeTimers.contains(type)) this->killTimer(d->typeTimers.take(type));
}

void CommandSender::setCommandStatus(Command::CommandType type, Command::CommandStatus status)
{
    this->removeCommand(type);

    emit commandStatusChanged(type, status);
}

void CommandSender::timerEvent(QTimerEvent* event)
{
    if (!d->typeTimers.values().contains(event->timerId())) return QObject::timerEvent(event);
    Command::CommandType type = d->typeTimers.key(event->timerId());

    emit sendCommand(d->typeCommands[type], ++d->typeAttemps[type]);
    if (d->typeAttemps[type] >= maxAttemps) this->setCommandStatus(type, Command::Rejected);
}

