#include "barometric_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_traits.h"

using namespace presentation;

BarometricPresenter::BarometricPresenter(domain::TelemetryNode* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void BarometricPresenter::onParametersChanged(const QVariantMap& parameters)
{
    if (parameters.contains(telemetry::altitude))
        this->setViewProperty(PROPERTY(barometricAltitude), parameters[telemetry::altitude]);
    if (parameters.contains(telemetry::climb))
        this->setViewProperty(PROPERTY(barometricClimb), parameters[telemetry::climb]);
}
