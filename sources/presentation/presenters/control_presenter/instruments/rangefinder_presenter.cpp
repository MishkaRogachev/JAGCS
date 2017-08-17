#include "rangefinder_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

RangefinderPresenter::RangefinderPresenter(domain::Telemetry* node, QObject* parent):
    AbstractTelemetryPresenter(node, parent)
{}

void RangefinderPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Enabled))
        this->setViewsProperty(PROPERTY(rangefinderEnabled), parameters[domain::Telemetry::Enabled]);
    if (parameters.contains(domain::Telemetry::Operational))
        this->setViewsProperty(PROPERTY(rangefinderOperational), parameters[domain::Telemetry::Operational]);
    if (parameters.contains(domain::Telemetry::Height))
        this->setViewsProperty(PROPERTY(rangefinderHeight), parameters[domain::Telemetry::Height]);
}
