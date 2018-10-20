#include "abstract_command_handler.h"

// Qt
#include <QMap>
#include <QTimerEvent>
#include <QDebug>

namespace
{
    const int interval = 500;
    const int maxAttemps = 5;
}

using namespace domain;

class AbstractCommandHandler::Impl
{
public:
    QMultiMap<int, dto::CommandPtr> vehicleCommands;
    QMap <dto::CommandPtr, int> attemps;
    QMap <dto::CommandPtr, int> commandTimers;
};

AbstractCommandHandler::AbstractCommandHandler(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

AbstractCommandHandler::~AbstractCommandHandler()
{}

void AbstractCommandHandler::executeCommand(int vehicleId, const dto::CommandPtr& command)
{
    for (const dto::CommandPtr& timedCommand: d->commandTimers.keys())
    {
        if (timedCommand->type() != command->type() ||
            !d->vehicleCommands.values(vehicleId).contains(timedCommand)) continue;

        this->stopCommand(vehicleId, timedCommand);

        timedCommand->setStatus(dto::Command::Canceled);
        emit commandChanged(timedCommand);

        break;
    }

    d->vehicleCommands.insert(vehicleId, command);
    d->attemps[command] = 0;
    d->commandTimers[command] = this->startTimer(::interval);
    command->setStatus(dto::Command::Sending);

    this->sendCommand(vehicleId, command);

    emit commandChanged(command);
}

void AbstractCommandHandler::cancelCommand(int vehicleId, dto::Command::CommandType type)
{
    this->ackCommand(vehicleId, type, dto::Command::Canceled);
}

void AbstractCommandHandler::ackCommand(int vehicleId, dto::Command::CommandType type,
                                        dto::Command::CommandStatus status)
{
    for (const dto::CommandPtr& command: d->vehicleCommands.values(vehicleId))
    {
        if (command->type() != type) continue;

        command->setStatus(status);
        if (command->isFinished()) this->stopCommand(vehicleId, command);

        emit commandChanged(command);
    }
}

void AbstractCommandHandler::stopCommand(int vehicleId, const dto::CommandPtr& command)
{
    if (d->commandTimers.contains(command))
    {
        this->killTimer(d->commandTimers.take(command));
    }
    d->vehicleCommands.remove(vehicleId, command);
    d->attemps.remove(command);
}

void AbstractCommandHandler::timerEvent(QTimerEvent* event)
{
    dto::CommandPtr command = d->commandTimers.key(event->timerId());
    if (command.isNull()) return QObject::timerEvent(event);

    int vehicleId = d->vehicleCommands.key(command, 0);
    this->sendCommand(vehicleId, command, ++d->attemps[command]);

    if (d->attemps[command] < ::maxAttemps) return;

    this->stopCommand(vehicleId, command);

    command->setStatus(dto::Command::Rejected);
    emit commandChanged(command);
}
