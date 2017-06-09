#include "ahrs_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_traits.h"

using namespace presentation;

AhrsPresenter::AhrsPresenter(domain::TelemetryNode* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void AhrsPresenter::onParametersChanged(const QVariantMap& parameters)
{
    for (const QString& key: parameters.keys())
    {
        if (key == telemetry::pitch) this->setViewProperty(PROPERTY(pitch), parameters[key]);
        if (key == telemetry::roll) this->setViewProperty(PROPERTY(roll), parameters[key]);
        if (key == telemetry::yaw) this->setViewProperty(PROPERTY(yaw), parameters[key]);
    }
}
