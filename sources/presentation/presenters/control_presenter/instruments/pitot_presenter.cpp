#include "pitot_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

PitotPresenter::PitotPresenter(domain::Telemetry* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void PitotPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Enabled))
        this->setViewProperty(PROPERTY(pitotEnabled),
                              parameters[domain::Telemetry::Enabled]);
    if (parameters.contains(domain::Telemetry::Operational))
        this->setViewProperty(PROPERTY(pitotOperational),
                              parameters[domain::Telemetry::Operational]);
    if (parameters.contains(domain::Telemetry::TrueAirspeed))
        this->setViewProperty(PROPERTY(trueAirspeed),
                              parameters[domain::Telemetry::TrueAirspeed]);
    if (parameters.contains(domain::Telemetry::IndicatedAirspeed))
        this->setViewProperty(PROPERTY(indicatedAirspeed),
                              parameters[domain::Telemetry::IndicatedAirspeed]);
}
