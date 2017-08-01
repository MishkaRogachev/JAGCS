#include "mission_command_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "command_service.h"
#include "command.h"

using namespace presentation;

class MissionCommandPresenter::Impl
{
public:
    domain::CommandService* service = nullptr;

    int vehicleId;
};

MissionCommandPresenter::MissionCommandPresenter(int vehicleId, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->service = domain::ServiceRegistry::commandService();
    d->vehicleId = vehicleId;
}

MissionCommandPresenter::~MissionCommandPresenter()
{}

void MissionCommandPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(commandReturn()), this, SLOT(onCommandReturn()));
    connect(view, SIGNAL(commandStart()), this, SLOT(onCommandStart()));
    connect(view, SIGNAL(pauseContinue(bool)), this, SLOT(onPauseContinue(bool)));
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
