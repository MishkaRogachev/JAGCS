#include "pitot_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_traits.h"

using namespace presentation;

PitotPresenter::PitotPresenter(domain::TelemetryNode* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void PitotPresenter::onParametersChanged(const domain::TelemetryMap& parameters)
{
    if (parameters.contains(domain::TelemetryId::TrueAirspeed))
        this->setViewProperty(PROPERTY(trueAirspeed),
                              parameters[domain::TelemetryId::TrueAirspeed]);
    if (parameters.contains(domain::TelemetryId::IndicatedAirspeed))
        this->setViewProperty(PROPERTY(indicatedAirspeed),
                              parameters[domain::TelemetryId::IndicatedAirspeed]);
}
