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

bool CommandSender::hasCommand(Command::CommandType type) const
{
    return d->typeCommands.contains(type);
}

Command CommandSender::takeCommand(Command::CommandType type)
{
    Command cmd = d->typeCommands.take(type);
    d->typeAttemps.remove(type);

    if (d->typeTimers.contains(type)) this->killTimer(d->typeTimers.take(type));
    return cmd;
}

void CommandSender::addCommand(const Command& command)
{
    if (d->typeTimers.contains(command.type())) this->killTimer(d->typeTimers.take(command.type()));

    d->typeCommands[command.type()] = command;
    d->typeAttemps[command.type()] = 0;

    emit sendCommand(command, d->typeAttemps[command.type()]);
    d->typeTimers[command.type()] = this->startTimer(::interval);
    d->typeCommands[command.type()].setStatus(Command::Sending);
    emit commandFinished(d->typeCommands[command.type()]);
}

void CommandSender::finishCommand(Command::CommandType type, Command::CommandStatus status)
{
    Command cmd = this->takeCommand(type);

    cmd.setStatus(status);

    emit commandFinished(cmd);
}

void CommandSender::timerEvent(QTimerEvent* event)
{
    if (!d->typeTimers.values().contains(event->timerId())) return QObject::timerEvent(event);
    Command::CommandType type = d->typeTimers.key(event->timerId());

    emit sendCommand(d->typeCommands[type], ++d->typeAttemps[type]);
    if (d->typeAttemps[type] >= maxAttemps) this->finishCommand(type, Command::Rejected);
}

