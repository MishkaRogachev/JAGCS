#include "navigator_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

NavigatorPresenter::NavigatorPresenter(domain::Telemetry* node, QObject* parent):
    AbstractTelemetryPresenter(node, parent)
{}

void NavigatorPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::TargetBearing))
        this->setViewsProperty(PROPERTY(targetBearing), parameters[domain::Telemetry::TargetBearing]);
    if (parameters.contains(domain::Telemetry::TargetDistance))
        this->setViewsProperty(PROPERTY(targetDistance), parameters[domain::Telemetry::TargetDistance]);
    if (parameters.contains(domain::Telemetry::TrackError))
        this->setViewsProperty(PROPERTY(trackError), parameters[domain::Telemetry::TrackError]);
}
