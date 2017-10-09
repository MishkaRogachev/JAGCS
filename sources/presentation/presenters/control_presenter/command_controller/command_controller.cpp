#include "command_controller.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "command_service.h"

using namespace presentation;

class CommandController::Impl
{
public:
    domain::CommandService* service = domain::ServiceRegistry::commandService();

    int vehicleId = 0;
};

CommandController::CommandController(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    connect(d->service, &domain::CommandService::commandStatusChanged,
            this, &CommandController::commandStatusChanged);
}

CommandController::~CommandController()
{}

void CommandController::setControlVehicle(int vehicleId)
{
    d->vehicleId = vehicleId;
}

void CommandController::executeCommand(int commandType, const QVariant& args)
{
    domain::Command command(domain::Command::CommandType(commandType), d->vehicleId);
    command.setArguments(args.toList());
    d->service->executeCommand(command);
}

void CommandController::rejectCommand(int commandType)
{
    d->service->rejectCommand(domain::Command::CommandType(commandType));
}



