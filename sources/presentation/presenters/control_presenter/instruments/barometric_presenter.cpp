#include "barometric_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

BarometricPresenter::BarometricPresenter(domain::Telemetry* node, QObject* parent):
    AbstractTelemetryPresenter(node, parent)
{}

void BarometricPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Enabled))
        this->setViewsProperty(PROPERTY(barometricEnabled), parameters[domain::Telemetry::Enabled]);
    if (parameters.contains(domain::Telemetry::Operational))
        this->setViewsProperty(PROPERTY(barometricOperational), parameters[domain::Telemetry::Operational]);
    if (parameters.contains(domain::Telemetry::Altitude))
        this->setViewsProperty(PROPERTY(barometricAltitude), parameters[domain::Telemetry::Altitude]);
    if (parameters.contains(domain::Telemetry::Climb))
        this->setViewsProperty(PROPERTY(barometricClimb), parameters[domain::Telemetry::Climb]);
}
