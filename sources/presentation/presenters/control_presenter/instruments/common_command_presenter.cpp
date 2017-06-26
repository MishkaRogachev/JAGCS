#include "common_command_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "command_service.h"
#include "command.h"

using namespace presentation;

class CommonCommandPresenter::Impl
{
public:
    domain::CommandService* service = nullptr;

    int vehicleId;
};

CommonCommandPresenter::CommonCommandPresenter(domain::CommandService* service,
                                               int vehicleId,
                                               QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->service = service;
    d->vehicleId = vehicleId;
}

CommonCommandPresenter::~CommonCommandPresenter()
{}

void CommonCommandPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(commandArmDisarm(bool)), this, SLOT(onCommandArmDisarm(bool)));
}

void CommonCommandPresenter::onCommandArmDisarm(bool arm)
{
    domain::Command command(domain::Command::ArmDisarm, d->vehicleId);
    command.addArgument(arm);
    d->service->executeCommand(command);
}
