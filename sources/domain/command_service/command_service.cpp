#include "command_service.h"

// Qt
#include <QQueue>

// Internal
#include "command.h"

using namespace domain;

class CommandService::Impl
{
public:
    QQueue<Command> commandQueue;
};

CommandService::CommandService(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

CommandService::~CommandService()
{}

Command CommandService::headCommand()
{
    return d->commandQueue.dequeue();
}

bool CommandService::hasCommand() const
{
    return d->commandQueue.isEmpty();
}

void CommandService::executeCommand(const Command& command)
{
    d->commandQueue.enqueue(command);

    emit gotCommand();
}
