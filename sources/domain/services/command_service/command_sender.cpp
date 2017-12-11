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
    QMap <dao::Command::CommandType, dao::CommandPtr> typeCommands;
    QMap <dao::Command::CommandType, int> typeAttemps;
    QMap <dao::Command::CommandType, int> typeTimers;
};

CommandSender::CommandSender(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

CommandSender::~CommandSender()
{}

bool CommandSender::hasCommand(dao::Command::CommandType type) const
{
    return d->typeCommands.contains(type);
}

dao::CommandPtr CommandSender::takeCommand(dao::Command::CommandType type)
{
    dao::CommandPtr cmd = d->typeCommands.take(type);
    d->typeAttemps.remove(type);

    if (d->typeTimers.contains(type)) this->killTimer(d->typeTimers.take(type));
    return cmd;
}

void CommandSender::addCommand(const dao::CommandPtr& command)
{
    if (d->typeTimers.contains(command->type()))
    {
        this->killTimer(d->typeTimers.take(command->type()));
    }

    d->typeCommands[command->type()] = command;
    d->typeAttemps[command->type()] = 0;

    emit sendCommand(command, d->typeAttemps[command->type()]);
    d->typeTimers[command->type()] = this->startTimer(::interval);
    d->typeCommands[command->type()]->setStatus(dao::Command::Sending);
    emit commandChanged(d->typeCommands[command->type()]);
}

void CommandSender::finishCommand(dao::Command::CommandType type, dao::Command::CommandStatus status)
{
    dao::CommandPtr cmd = this->takeCommand(type);

    cmd->setStatus(status);

    emit commandChanged(cmd);
}

void CommandSender::timerEvent(QTimerEvent* event)
{
    if (!d->typeTimers.values().contains(event->timerId())) return QObject::timerEvent(event);
    dao::Command::CommandType type = d->typeTimers.key(event->timerId());

    emit sendCommand(d->typeCommands[type], ++d->typeAttemps[type]);
    if (d->typeAttemps[type] >= maxAttemps) this->finishCommand(type, dao::Command::Rejected);
}

