#include "abstract_telemetry_presenter.h"

// Qt
#include <QDebug>

//Internal
#include "service_registry.h"
#include "telemetry_service.h"

using namespace presentation;

AbstractTelemetryPresenter::AbstractTelemetryPresenter(QObject* parent):
    BaseDisplayPresenter(parent)
{}

void AbstractTelemetryPresenter::setVehicle(int vehicleId)
{
    BaseDisplayPresenter::setVehicle(vehicleId);

    domain::Telemetry* node = domain::ServiceRegistry::telemetryService()->vehicleNode(vehicleId);
    if (m_node == node) return;

    if (m_node) this->disconnectNode();

    m_node = node;

    if (node) this->connectNode(node);
}

void AbstractTelemetryPresenter::disconnectNode()
{
    disconnect(m_node, 0, this, 0);
}

void AbstractTelemetryPresenter::chainNode(
        domain::Telemetry* node, std::function<void(const domain::Telemetry::TelemetryMap&)> func)
{
    if (node) QObject::connect(node, &domain::Telemetry::parametersUpdated, this, func);
    func(node ? node->parameters() : domain::Telemetry::TelemetryMap());
}
