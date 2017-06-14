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
    if (parameters.contains(telemetry::pitch))
        this->setViewProperty(PROPERTY(pitch), parameters[telemetry::pitch]);
    if (parameters.contains(telemetry::roll))
        this->setViewProperty(PROPERTY(roll), parameters[telemetry::roll]);
    if (parameters.contains(telemetry::yawspeed))
        this->setViewProperty(PROPERTY(yawspeed), parameters[telemetry::yawspeed]);
}
