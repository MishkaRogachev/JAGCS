#include "compass_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

CompassPresenter::CompassPresenter(domain::Telemetry* node, QObject* parent):
    AbstractTelemetryPresenter(node, parent)
{}

void CompassPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Enabled))
        this->setViewsProperty(PROPERTY(compassEnabled), parameters[domain::Telemetry::Enabled]);
    if (parameters.contains(domain::Telemetry::Operational))
        this->setViewsProperty(PROPERTY(compassOperational), parameters[domain::Telemetry::Operational]);
    if (parameters.contains(domain::Telemetry::Heading))
        this->setViewsProperty(PROPERTY(heading), parameters[domain::Telemetry::Heading]);
}
