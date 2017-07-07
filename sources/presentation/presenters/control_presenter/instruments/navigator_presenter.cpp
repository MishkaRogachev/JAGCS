#include "navigator_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

NavigatorPresenter::NavigatorPresenter(domain::Telemetry* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void NavigatorPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::TargetBearing))
        this->setViewProperty(PROPERTY(targetBearing), parameters[domain::Telemetry::TargetBearing]);
    if (parameters.contains(domain::Telemetry::TargetDistance))
        this->setViewProperty(PROPERTY(targetDistance), parameters[domain::Telemetry::TargetDistance]);
    if (parameters.contains(domain::Telemetry::TrackError))
        this->setViewProperty(PROPERTY(trackError), parameters[domain::Telemetry::TrackError]);
    if (parameters.contains(domain::Telemetry::CurrentWaypoint))
        this->setViewProperty(PROPERTY(waypoint), parameters[domain::Telemetry::CurrentWaypoint]);
}
