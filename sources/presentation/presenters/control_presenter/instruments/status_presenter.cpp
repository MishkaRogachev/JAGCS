#include "status_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_traits.h"

using namespace presentation;

StatusPresenter::StatusPresenter(domain::TelemetryNode* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void StatusPresenter::onParametersChanged(const domain::TelemetryMap& parameters)
{
    if (parameters.contains(domain::TelemetryId::Online))
        this->setViewProperty(PROPERTY(online), parameters[domain::TelemetryId::Online]);
    if (parameters.contains(domain::TelemetryId::Armed))
        this->setViewProperty(PROPERTY(armed), parameters[domain::TelemetryId::Armed]);
    if (parameters.contains(domain::TelemetryId::Mode))
        this->setViewProperty(PROPERTY(mode), parameters[domain::TelemetryId::Mode]);
}
