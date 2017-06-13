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
    for (const QString& key: parameters.keys())
    {
        if (key == telemetry::trueAirspeed)
            this->setViewProperty(PROPERTY(trueAirspeed), parameters[key]);
        if (key == telemetry::indicatedAirspeed)
            this->setViewProperty(PROPERTY(indicatedAirspeed), parameters[key]);
    }
}
