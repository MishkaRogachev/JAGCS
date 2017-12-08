#include "control_display_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "command_service.h"

using namespace presentation;

ControlDisplayPresenter::ControlDisplayPresenter(QObject* parent):
    AbstractInstrumentPresenter(parent),
    m_service(domain::ServiceRegistry::commandService())
{
    connect(m_service, &domain::CommandService::commandStatusChanged,
            this, &ControlDisplayPresenter::onCommandStatusChanged);
}

void ControlDisplayPresenter::executeCommand(int commandType, const QVariant& args)
{
    domain::Command command(domain::Command::CommandType(commandType), this->vehicleId());
    command.setArguments(args.toList());
    m_service->executeCommand(command);
}

void ControlDisplayPresenter::rejectCommand(int commandType)
{
    m_service->rejectCommand(domain::Command::CommandType(commandType));
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
    this->setViewProperty(PROPERTY(availableModes), parameters.value(domain::Telemetry::AvailableModes));
}

void ControlDisplayPresenter::onCommandStatusChanged(domain::Command::CommandType type,
                                                     domain::Command::CommandStatus status)
{
    // TODO: coommand feedback
}
