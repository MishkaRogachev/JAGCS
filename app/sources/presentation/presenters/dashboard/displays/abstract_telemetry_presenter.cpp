#include "abstract_telemetry_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

AbstractTelemetryPresenter::AbstractTelemetryPresenter(QObject* parent):
    BasePresenter(parent)
{}

void AbstractTelemetryPresenter::setNode(data_source::Telemetry* node)
{
    if (m_node == node) return;

    if (m_node) this->disconnectNode();

    m_node = node;

    if (node) this->connectNode(node);
}

void AbstractTelemetryPresenter::disconnectNode()
{
    disconnect(m_node, 0, this, 0);
}

void AbstractTelemetryPresenter::chainNode(data_source::Telemetry* node,
                              std::function<void(const data_source::Telemetry::TelemetryMap&)> func)
{
    if (node) QObject::connect(node, &data_source::Telemetry::parametersUpdated, this, func);
    func(node ? node->parameters() : data_source::Telemetry::TelemetryMap());
}
