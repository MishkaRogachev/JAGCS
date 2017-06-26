#include "command_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "command_service.h"
#include "command.h"

using namespace presentation;

class CommandPresenter::Impl
{
public:
    domain::CommandService* service = nullptr;

    int vehicleId;
};

CommandPresenter::CommandPresenter(domain::CommandService* service, int vehicleId,
                                   QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->service = service;
    d->vehicleId = vehicleId;
}

CommandPresenter::~CommandPresenter()
{}

void CommandPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(commandArmDisarm(bool)), this, SLOT(onCommandArmDisarm(bool)));
}

void CommandPresenter::onCommandArmDisarm(bool arm)
{
    domain::Command command(domain::Command::ArmDisarm, d->vehicleId);
    command.addArgument(arm);
    d->service->executeCommand(command);
}
