#include "command_instrument_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "command_service.h"
#include "command.h"

using namespace presentation;

class CommandInstrumentPresenter::Impl
{
public:
    domain::CommandService* service = nullptr;

    int vehicleId;
};

CommandInstrumentPresenter::CommandInstrumentPresenter(int vehicleId, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->service = domain::ServiceRegistry::commandService();
    d->vehicleId = vehicleId;
}

CommandInstrumentPresenter::~CommandInstrumentPresenter()
{}

void CommandInstrumentPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(commandReturn()), this, SLOT(onCommandReturn()));
    connect(view, SIGNAL(commandStart()), this, SLOT(onCommandStart()));
    connect(view, SIGNAL(pauseContinue(bool)), this, SLOT(onPauseContinue(bool)));
}


void CommandInstrumentPresenter::onCommandReturn()
{
    domain::Command command(domain::Command::Return, d->vehicleId);
    d->service->executeCommand(command);
}

void CommandInstrumentPresenter::onCommandStart()
{
    domain::Command command(domain::Command::Start, d->vehicleId);
    d->service->executeCommand(command);
}

void CommandInstrumentPresenter::onPauseContinue(bool unpause)
{
    domain::Command command(domain::Command::PauseContinue, d->vehicleId);
    command.addArgument(unpause);
    d->service->executeCommand(command);
}
