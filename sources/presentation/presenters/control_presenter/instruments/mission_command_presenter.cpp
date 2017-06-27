#include "mission_command_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "command_service.h"
#include "command.h"

using namespace presentation;

class MissionCommandPresenter::Impl
{
public:
    domain::CommandService* service = nullptr;

    int vehicleId;
};

MissionCommandPresenter::MissionCommandPresenter(domain::CommandService* service,
                                                 int vehicleId,
                                                 QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->service = service;
    d->vehicleId = vehicleId;
}

MissionCommandPresenter::~MissionCommandPresenter()
{}

void MissionCommandPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(commandJumpTo(int)), this, SLOT(onCommandJumpTo(int)));
    connect(view, SIGNAL(commandReturn()), this, SLOT(onCommandReturn()));
    connect(view, SIGNAL(commandStart()), this, SLOT(onCommandStart()));
    connect(view, SIGNAL(pauseContinue(bool)), this, SLOT(onPauseContinue(bool)));
}

void MissionCommandPresenter::onCommandJumpTo(int item)
{
    domain::Command command(domain::Command::Jump, d->vehicleId);
    command.addArgument(item);
    d->service->executeCommand(command);
}

void MissionCommandPresenter::onCommandReturn()
{
    domain::Command command(domain::Command::Return, d->vehicleId);
    d->service->executeCommand(command);
}

void MissionCommandPresenter::onCommandStart()
{
    domain::Command command(domain::Command::Start, d->vehicleId);
    d->service->executeCommand(command);
}

void MissionCommandPresenter::onPauseContinue(bool unpause)
{
    domain::Command command(domain::Command::PauseContinue, d->vehicleId);
    command.addArgument(unpause);
    d->service->executeCommand(command);
}
