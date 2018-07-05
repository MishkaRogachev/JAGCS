#include "command_service.h"

// Qt
#include <QMap>

// Internal
#include "abstract_command_handler.h"

using namespace domain;

CommandService::CommandService(QObject* parent):
    QObject(parent)
{
    qRegisterMetaType<dto::CommandPtr>("dto::CommandPtr");
    qRegisterMetaType<dto::Command::CommandType>("dto::Command::CommandType");
    qRegisterMetaType<dto::Command::CommandStatus>("dto::Command::CommandStatus");
}

void CommandService::addHandler(AbstractCommandHandler* handler)
{
    connect(this, &CommandService::executeCommand, handler, &AbstractCommandHandler::executeCommand);
    connect(this, &CommandService::cancelCommand, handler, &AbstractCommandHandler::cancelCommand);

    connect(handler, &AbstractCommandHandler::commandChanged, this, &CommandService::commandChanged);
}

void CommandService::removeHandler(AbstractCommandHandler* handler)
{
    disconnect(this, 0, handler, 0);
    disconnect(handler, 0, this, 0);
}
