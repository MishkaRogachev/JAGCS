#include "status_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_traits.h"

using namespace presentation;

StatusPresenter::StatusPresenter(domain::TelemetryNode* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void StatusPresenter::onParametersChanged(const QVariantMap& parameters)
{
    if (parameters.contains(telemetry::online))
        this->setViewProperty(PROPERTY(online), parameters[telemetry::online]);
    if (parameters.contains(telemetry::armed))
        this->setViewProperty(PROPERTY(armed), parameters[telemetry::armed]);
    if (parameters.contains(telemetry::mode))
        this->setViewProperty(PROPERTY(mode), parameters[telemetry::mode]);
}
