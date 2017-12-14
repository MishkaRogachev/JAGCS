#include "abstract_command_handler.h"

// Qt
#include <QMap>
#include <QTimerEvent>
#include <QDebug>

namespace
{
    const int interval = 700;
    const int maxAttemps = 5;
}

using namespace domain;

class AbstractCommandHandler::Impl
{
public:
    QMultiMap<int, dao::CommandPtr> vehicleCommands;
    QMap <dao::CommandPtr, int> attemps;
    QMap <dao::CommandPtr, int> commandTimers;
};

AbstractCommandHandler::AbstractCommandHandler(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

AbstractCommandHandler::~AbstractCommandHandler()
{}

void AbstractCommandHandler::executeCommand(int vehicleId, const dao::CommandPtr& command)
{
    for (const dao::CommandPtr& timedCommand: d->commandTimers.keys())
    {
        if (timedCommand->type() != command->type() ||
            !d->vehicleCommands.values(vehicleId).contains(timedCommand)) continue;

        this->stopCommand(vehicleId, command);

        timedCommand->setStatus(dao::Command::Canceled);
        emit commandChanged(timedCommand);

        break;
    }

    d->vehicleCommands.insert(vehicleId, command);
    d->attemps[command] = 0;
    d->commandTimers[command] = this->startTimer(::interval);
    command->setStatus(dao::Command::Sending);

    this->sendCommand(vehicleId, command);

    emit commandChanged(command);
}

void AbstractCommandHandler::cancelCommand(int vehicleId, dao::Command::CommandType type)
{
    this->ackCommand(vehicleId, type, dao::Command::Canceled);
}

void AbstractCommandHandler::ackCommand(int vehicleId, dao::Command::CommandType type,
                                        dao::Command::CommandStatus status)
{
    for (const dao::CommandPtr& command: d->vehicleCommands.values(vehicleId))
    {
        if (command->type() != type) continue;

        this->stopCommand(vehicleId, command);

        command->setStatus(status);
        emit commandChanged(command);
    }
}

void AbstractCommandHandler::stopCommand(int vehicleId, const dao::CommandPtr& command)
{
    d->vehicleCommands.remove(vehicleId, command);
    d->attemps.remove(command);
    if (d->commandTimers.contains(command))
    {
        this->killTimer(d->commandTimers.take(command));
    }
}

void AbstractCommandHandler::timerEvent(QTimerEvent* event)
{
    dao::CommandPtr command = d->commandTimers.key(event->timerId());
    if (command.isNull()) return QObject::timerEvent(event);

    int vehicleId = d->vehicleCommands.key(command, 0);
    this->sendCommand(vehicleId, command, ++d->attemps[command]);

    if (d->attemps[command] < ::maxAttemps) return;

    this->stopCommand(vehicleId, command);

    command->setStatus(dao::Command::Rejected);
    emit commandChanged(command);
}
