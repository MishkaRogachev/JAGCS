#include "command_instrument_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "command_service.h"
#include "command.h"

using namespace domain;
using namespace presentation;

class CommandInstrumentPresenter::Impl
{
public:
    CommandService* service = nullptr;

    int vehicleId;
};

CommandInstrumentPresenter::CommandInstrumentPresenter(int vehicleId, QObject* parent):
    BaseInstrumentPresenter(parent),
    d(new Impl())
{
    d->service = ServiceRegistry::commandService();
    d->vehicleId = vehicleId;

    connect(d->service, &CommandService::commandStatusChanged,
            this, &CommandInstrumentPresenter::onCommandStatusChanged);
}

CommandInstrumentPresenter::~CommandInstrumentPresenter()
{}

void CommandInstrumentPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(executeCommand(int)), this, SLOT(onExecuteCommand(int)));
    connect(view, SIGNAL(executeBoolCommand(int, bool)), this, SLOT(onExecuteBoolCommand(int, bool)));
    connect(view, SIGNAL(rejectCommand(int)), this, SLOT(onRejectCommand(int)));
}

void CommandInstrumentPresenter::onExecuteCommand(int commandType)
{
    Command command(Command::CommandType(commandType), d->vehicleId);
    d->service->executeCommand(command);
}

void CommandInstrumentPresenter::onExecuteBoolCommand(int commandType, bool check)
{
    Command command(Command::CommandType(commandType), d->vehicleId);
    command.addArgument(check);
    d->service->executeCommand(command);
}

void CommandInstrumentPresenter::onRejectCommand(int commandType)
{
    d->service->rejectCommand(Command::CommandType(commandType));
}

void CommandInstrumentPresenter::onCommandStatusChanged(Command::CommandType type,
                                                        Command::CommandStatus status)
{
    for (QObject* view: m_views)
    {
        QMetaObject::invokeMethod(view, "commandStatusChanged",
                                  Q_ARG(QVariant, type), Q_ARG(QVariant, status));
    }
}
