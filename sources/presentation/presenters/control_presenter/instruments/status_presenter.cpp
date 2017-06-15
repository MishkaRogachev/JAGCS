#include "status_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

StatusPresenter::StatusPresenter(domain::Telemetry* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void StatusPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Online))
        this->setViewProperty(PROPERTY(online), parameters[domain::Telemetry::Online]);
    if (parameters.contains(domain::Telemetry::Armed))
        this->setViewProperty(PROPERTY(armed), parameters[domain::Telemetry::Armed]);
    if (parameters.contains(domain::Telemetry::Mode))
        this->setViewProperty(PROPERTY(mode), parameters[domain::Telemetry::Mode]);
}
