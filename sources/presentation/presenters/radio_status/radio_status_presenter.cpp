#include "radio_status_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

RadioStatusPresenter::RadioStatusPresenter(QObject* parent):
    BasePresenter(parent)
    //m_node(node)
{
//    connect(node, &domain::Telemetry::parametersChanged,
//            this, &RadioPresenter::onParametersChanged);
}

void RadioStatusPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Rssi))
        this->setViewProperty(PROPERTY(rssi), parameters[domain::Telemetry::Rssi]);
    if (parameters.contains(domain::Telemetry::RemoteRssi))
        this->setViewProperty(PROPERTY(remoteRssi), parameters[domain::Telemetry::RemoteRssi]);
}

void RadioStatusPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->onParametersChanged(m_node->parameters());
}
