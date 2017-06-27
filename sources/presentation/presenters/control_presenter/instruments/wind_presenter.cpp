#include "wind_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

WindPresenter::WindPresenter(domain::Telemetry* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void WindPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Yaw))
        this->setViewProperty(PROPERTY(windDirection), parameters[domain::Telemetry::Yaw]);
    if (parameters.contains(domain::Telemetry::Speed))
        this->setViewProperty(PROPERTY(windSpeed), parameters[domain::Telemetry::Speed]);
}
