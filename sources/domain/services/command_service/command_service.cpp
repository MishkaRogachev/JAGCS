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
    qRegisterMetaType<dao::CommandPtr>("dao::CommandPtr");
}

CommandService::~CommandService()
{}

void CommandService::executeCommand(int vehicleId, const dao::CommandPtr& command)
{
    if (vehicleId == 0 || command->type() == dao::Command::UnknownCommand)
    {
        command->setStatus(dao::Command::Rejected);
        emit commandChanged(command);
        return;
    }

    CommandSender* sender = d->senders.value(vehicleId, nullptr);
    if (!sender)
    {
        sender = new CommandSender(this);
        d->senders[vehicleId] = sender;
        connect(sender, &CommandSender::commandChanged, this, &CommandService::commandChanged);
    }

    sender->addCommand(command);
}

void CommandService::cancelCommand(int vehicleId, dao::Command::CommandType type)
{
    if (!d->senders.contains(vehicleId) || !d->senders[vehicleId]->hasCommand(type)) return;

    dao::CommandPtr command = d->senders[vehicleId]->takeCommand(type);
    command->setStatus(dao::Command::Canceled);
    emit commandChanged(command);
}
