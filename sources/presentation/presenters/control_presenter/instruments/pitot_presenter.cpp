#include "pitot_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

PitotPresenter::PitotPresenter(domain::Telemetry* node, QObject* parent):
    AbstractTelemetryPresenter(node, parent)
{}

void PitotPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Enabled))
        this->setViewsProperty(PROPERTY(pitotEnabled), parameters[domain::Telemetry::Enabled]);
    if (parameters.contains(domain::Telemetry::Operational))
        this->setViewsProperty(PROPERTY(pitotOperational), parameters[domain::Telemetry::Operational]);
    if (parameters.contains(domain::Telemetry::TrueAirspeed))
        this->setViewsProperty(PROPERTY(trueAirspeed), parameters[domain::Telemetry::TrueAirspeed]);
    if (parameters.contains(domain::Telemetry::IndicatedAirspeed))
        this->setViewsProperty(PROPERTY(indicatedAirspeed), parameters[domain::Telemetry::IndicatedAirspeed]);
}
