#include "pitot_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_traits.h"

using namespace presentation;

PitotPresenter::PitotPresenter(domain::TelemetryNode* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void PitotPresenter::onParametersChanged(const QVariantMap& parameters)
{
    if (parameters.contains(telemetry::trueAirspeed))
        this->setViewProperty(PROPERTY(trueAirspeed), parameters[telemetry::trueAirspeed]);
    if (parameters.contains(telemetry::indicatedAirspeed))
        this->setViewProperty(PROPERTY(indicatedAirspeed), parameters[telemetry::indicatedAirspeed]);
}
