#include "command_service.h"

// Qt
#include <QMap>

// Internal
#include "command_sender.h"

using namespace domain;

class CommandService::Impl
{
public:
    QMap<int, CommandSender*> senders;
};

CommandService::CommandService(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    qRegisterMetaType<Command>("Command");
    qRegisterMetaType<Command::CommandType>("Command::CommandType");
    qRegisterMetaType<Command::CommandStatus>("Command::CommandStatus");
}

CommandService::~CommandService()
{}

void CommandService::executeCommand(int vehicleId, const Command& command)
{
    if (vehicleId == 0 || command.type() == Command::UnknownCommand)
    {
//        command.setStatus(Command::Rejected);
//        emit commandStatusChanged(command);
        return;
    }

    d->senders.value(vehicleId, new CommandSender(this))->addCommand(command);
}

void CommandService::rejectCommand(int vehicleId, Command::CommandType type)
{
    if (!d->senders.contains(vehicleId)
        || !d->senders[vehicleId]->hasCommand(type)) return;

    Command command = d->senders[vehicleId]->takeCommand(type);
    command.setStatus(Command::Canceled);
    emit commandStatusChanged(command);
}
