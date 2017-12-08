#include "abstract_instrument_presenter.h"

// Qt
#include <QDebug>

//Internal
#include "service_registry.h"
#include "telemetry_service.h"

using namespace presentation;

AbstractInstrumentPresenter::AbstractInstrumentPresenter(QObject* parent):
    BasePresenter(parent)
{}

int AbstractInstrumentPresenter::vehicleId() const
{
    return m_vehicleId;
}

void AbstractInstrumentPresenter::setVehicle(int vehicleId)
{
    m_vehicleId = vehicleId;

    domain::TelemetryService* service = domain::ServiceRegistry::telemetryService();
    domain::Telemetry* node = service->vehicleNode(vehicleId);
    if (m_node == node) return;

    if (m_node) this->disconnectNode();

    m_node = node;

    if (node) this->connectNode(node);
}

void AbstractInstrumentPresenter::disconnectNode()
{
    disconnect(m_node, 0, this, 0);
}

void AbstractInstrumentPresenter::chainNode(
        domain::Telemetry* node, std::function<void(const domain::Telemetry::TelemetryMap&)> f)
{
    if (node) QObject::connect(node, &domain::Telemetry::parametersUpdated, this, f);
    f(node ? node->parameters() : domain::Telemetry::TelemetryMap());
}
