#include "command_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "command_service.h"

using namespace presentation;

class CommandPresenter::Impl
{
public:
    domain::CommandService* service = domain::ServiceRegistry::commandService();

    int vehicleId = 0;
};

CommandPresenter::CommandPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    connect(d->service, &domain::CommandService::commandStatusChanged,
            this, &CommandPresenter::onCommandStatusChanged);;
}

CommandPresenter::~CommandPresenter()
{}

void CommandPresenter::setControlVehicle(int vehicleId)
{
    d->vehicleId = vehicleId;
}

void CommandPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(executeCommand(int, QVariant)), this, SLOT(onExecuteCommand(int, QVariant)));
    connect(view, SIGNAL(rejectCommand(int)), this, SLOT(onRejectCommand(int)));
}

void CommandPresenter::onExecuteCommand(int commandType, const QVariant& args)
{
    domain::Command command(domain::Command::CommandType(commandType), d->vehicleId);
    command.setArguments(args.toList());
    d->service->executeCommand(command);
}

void CommandPresenter::onRejectCommand(int commandType)
{
    d->service->rejectCommand(domain::Command::CommandType(commandType));
}

void CommandPresenter::onCommandStatusChanged(domain::Command::CommandType type,
                                              domain::Command::CommandStatus status)
{
    this->invokeViewMethod("commandStatusChanged", type, status);
}


