#include "abstract_display_presenter.h"

// Qt
#include <QDebug>

//Internal
#include "service_registry.h"
#include "telemetry_service.h"

using namespace presentation;

AbstractDisplayPresenter::AbstractDisplayPresenter(QObject* parent):
    BasePresenter(parent)
{}

int AbstractDisplayPresenter::vehicleId() const
{
    return m_vehicleId;
}

void AbstractDisplayPresenter::setVehicle(int vehicleId)
{
    m_vehicleId = vehicleId;

    domain::TelemetryService* service = domain::ServiceRegistry::telemetryService();
    domain::Telemetry* node = service->vehicleNode(vehicleId);
    if (m_node == node) return;

    if (m_node) this->disconnectNode();

    m_node = node;

    if (node) this->connectNode(node);
}

void AbstractDisplayPresenter::disconnectNode()
{
    disconnect(m_node, 0, this, 0);
}

void AbstractDisplayPresenter::chainNode(
        domain::Telemetry* node, std::function<void(const domain::Telemetry::TelemetryMap&)> f)
{
    if (node) QObject::connect(node, &domain::Telemetry::parametersUpdated, this, f);
    f(node ? node->parameters() : domain::Telemetry::TelemetryMap());
}
