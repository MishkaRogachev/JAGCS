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
    connect(view, SIGNAL(commandReturn()), this, SLOT(onCommandReturn()));
    connect(view, SIGNAL(commandStart()), this, SLOT(onCommandStart()));
    connect(view, SIGNAL(commandJumpTo(int)), this, SLOT(onCommandJumpTo(int)));
}

void CommandPresenter::onCommandArmDisarm(bool arm)
{
    domain::Command command(domain::Command::ArmDisarm, d->vehicleId);
    command.addArgument(arm);
    d->service->executeCommand(command);
}

void CommandPresenter::onCommandReturn()
{
    domain::Command command(domain::Command::Return, d->vehicleId);
    d->service->executeCommand(command);
}

void CommandPresenter::onCommandStart()
{
    domain::Command command(domain::Command::Start, d->vehicleId);
    d->service->executeCommand(command);
}

void CommandPresenter::onCommandJumpTo(int item)
{
    domain::Command command(domain::Command::Jump, d->vehicleId);
    command.addArgument(item);
    d->service->executeCommand(command);
}
