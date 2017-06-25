#include "radio_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

RadioPresenter::RadioPresenter(domain::Telemetry* node, QObject* parent):
    BasePresenter(parent),
    m_node(node)
{
    connect(node, &domain::Telemetry::parametersChanged,
            this, &RadioPresenter::onParametersChanged);
}

void RadioPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Rssi))
        this->setViewProperty(PROPERTY(rssi), parameters[domain::Telemetry::Rssi]);
    if (parameters.contains(domain::Telemetry::RemoteRssi))
        this->setViewProperty(PROPERTY(remoteRssi), parameters[domain::Telemetry::RemoteRssi]);
}

void RadioPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->onParametersChanged(m_node->parameters());
}
