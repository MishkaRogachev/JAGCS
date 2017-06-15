#include "ahrs_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_traits.h"

using namespace presentation;

AhrsPresenter::AhrsPresenter(domain::TelemetryNode* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void AhrsPresenter::onParametersChanged(const domain::TelemetryMap& parameters)
{
    if (parameters.contains(domain::TelemetryId::Pitch))
        this->setViewProperty(PROPERTY(pitch),
                              parameters[domain::TelemetryId::Pitch]);
    if (parameters.contains(domain::TelemetryId::Roll))
        this->setViewProperty(PROPERTY(roll),
                              parameters[domain::TelemetryId::Roll]);
    if (parameters.contains(domain::TelemetryId::YawSpeed))
        this->setViewProperty(PROPERTY(yawspeed),
                              parameters[domain::TelemetryId::YawSpeed]);
}
