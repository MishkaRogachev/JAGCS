#include "wind_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

WindPresenter::WindPresenter(domain::Telemetry* node, QObject* parent):
    AbstractTelemetryPresenter(node, parent)
{}

void WindPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Yaw))
        this->setViewsProperty(PROPERTY(windDirection), parameters[domain::Telemetry::Yaw]);
    if (parameters.contains(domain::Telemetry::Speed))
        this->setViewsProperty(PROPERTY(windSpeed), parameters[domain::Telemetry::Speed]);
}
