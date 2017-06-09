#include "attitude_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry.h"

using namespace presentation;

AttitudePresenter::AttitudePresenter(domain::TelemetryNode* node, QObject* parent):
    AbstractInstrumentPresenter(parent),
    m_node(node)
{
    connect(node, &domain::TelemetryNode::parametersChanged,
            this, &AttitudePresenter::onParametersChanged);
}

void AttitudePresenter::onParametersChanged(const QVariantMap& parameters)
{
    qDebug() << parameters;
    for (const QString& key: parameters.keys())
    {
        if (key == telemetry::pitch) this->setViewProperty(PROPERTY(pitch), parameters[key]);
        if (key == telemetry::roll) this->setViewProperty(PROPERTY(roll), parameters[key]);
        if (key == telemetry::yaw) this->setViewProperty(PROPERTY(yaw), parameters[key]);
    }
}

void AttitudePresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->onParametersChanged(m_node->parameters());
}
