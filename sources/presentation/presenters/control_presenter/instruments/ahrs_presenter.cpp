#include "ahrs_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

AhrsPresenter::AhrsPresenter(domain::Telemetry* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void AhrsPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Pitch))
        this->setViewProperty(PROPERTY(pitch),
                              parameters[domain::Telemetry::Pitch]);
    if (parameters.contains(domain::Telemetry::Roll))
        this->setViewProperty(PROPERTY(roll),
                              parameters[domain::Telemetry::Roll]);
    if (parameters.contains(domain::Telemetry::YawSpeed))
        this->setViewProperty(PROPERTY(yawspeed),
                              parameters[domain::Telemetry::YawSpeed]);
}
