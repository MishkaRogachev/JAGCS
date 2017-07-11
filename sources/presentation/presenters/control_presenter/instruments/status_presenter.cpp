#include "status_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

StatusPresenter::StatusPresenter(domain::Telemetry* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void StatusPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Armed))
        this->setViewProperty(PROPERTY(armed), parameters[domain::Telemetry::Armed]);
    if (parameters.contains(domain::Telemetry::Auto))
        this->setViewProperty(PROPERTY(automatic), parameters[domain::Telemetry::Auto]);
    if (parameters.contains(domain::Telemetry::Guided))
        this->setViewProperty(PROPERTY(guided), parameters[domain::Telemetry::Guided]);
    if (parameters.contains(domain::Telemetry::Stabilized))
        this->setViewProperty(PROPERTY(stabilized), parameters[domain::Telemetry::Stabilized]);
    if (parameters.contains(domain::Telemetry::Manual))
        this->setViewProperty(PROPERTY(manual), parameters[domain::Telemetry::Manual]);

    if (parameters.contains(domain::Telemetry::Mode))
        this->setViewProperty(PROPERTY(mode), parameters[domain::Telemetry::Mode]);
}
