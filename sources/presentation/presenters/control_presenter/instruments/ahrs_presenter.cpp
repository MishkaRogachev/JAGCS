#include "ahrs_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

AhrsPresenter::AhrsPresenter(domain::Telemetry* node, QObject* parent):
    AbstractTelemetryPresenter(node, parent)
{}

void AhrsPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Enabled))
        this->setViewsProperty(PROPERTY(ahrsEnabled), parameters[domain::Telemetry::Enabled]);
    if (parameters.contains(domain::Telemetry::Operational))
        this->setViewsProperty(PROPERTY(ahrsOperational), parameters[domain::Telemetry::Operational]);
    if (parameters.contains(domain::Telemetry::Pitch))
        this->setViewsProperty(PROPERTY(pitch), parameters[domain::Telemetry::Pitch]);
    if (parameters.contains(domain::Telemetry::Roll))
        this->setViewsProperty(PROPERTY(roll), parameters[domain::Telemetry::Roll]);
    if (parameters.contains(domain::Telemetry::Yaw))
        this->setViewsProperty(PROPERTY(yaw), parameters[domain::Telemetry::Yaw]);
    if (parameters.contains(domain::Telemetry::YawSpeed))
        this->setViewsProperty(PROPERTY(yawspeed), parameters[domain::Telemetry::YawSpeed]);
}
