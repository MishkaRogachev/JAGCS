#include "control_display_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "command.h"

#include "service_registry.h"
#include "command_service.h"

#include "modes.h"

using namespace presentation;

class ControlDisplayPresenter::Impl
{
public:
    domain::CommandService* service = domain::ServiceRegistry::commandService();
    QList<dao::CommandPtr> commands;
};

ControlDisplayPresenter::ControlDisplayPresenter(QObject* parent):
    AbstractTelemetryPresenter(parent),
    d(new Impl())
{
    connect(d->service, &domain::CommandService::commandChanged,
            this, [this](const dao::CommandPtr& command) {
        if (!d->commands.contains(command)) return;

        this->invokeViewMethod(PROPERTY(updateCommandStatus), command->type(), command->status());
        if (command->isFinished()) d->commands.removeOne(command);
    });
}

ControlDisplayPresenter::~ControlDisplayPresenter()
{}

void ControlDisplayPresenter::executeCommand(int commandType, const QVariant& args)
{
    dao::CommandPtr command = dao::CommandPtr::create();
    command->setType(dao::Command::CommandType(commandType));
    command->setArguments(args.toList());

    d->commands.append(command);
    d->service->executeCommand(this->vehicleId(), command);
}

void ControlDisplayPresenter::rejectCommand(int commandType)
{
    d->service->cancelCommand(this->vehicleId(), dao::Command::CommandType(commandType));
}

void ControlDisplayPresenter::connectNode(domain::Telemetry* node)
{
    this->chainNode(node->childNode(domain::Telemetry::Status),
                    std::bind(&ControlDisplayPresenter::updateStatus, this, std::placeholders::_1));
}

void ControlDisplayPresenter::updateStatus(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(armed), parameters.value(domain::Telemetry::Armed));
    this->setViewProperty(PROPERTY(guided), parameters.value(domain::Telemetry::Guided));
    this->setViewProperty(PROPERTY(mode), parameters.value(domain::Telemetry::Mode));

    QVariantList modes;
    for (auto item: parameters.value(domain::Telemetry::AvailableModes).value<
         QList<domain::Mode> >())
    {
        if (item == domain::Mode::Return) continue; // special button for return

        modes.append(QVariant::fromValue(item));
    }
    this->setViewProperty(PROPERTY(availableModes), modes);
}
