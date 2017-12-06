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

void AbstractInstrumentPresenter::setVehicle(int vehicleId)
{
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
    if (node) QObject::connect(node, &domain::Telemetry::parametersChanged, this, f);
    f(node ? node->parameters() : domain::Telemetry::TelemetryMap());
}
