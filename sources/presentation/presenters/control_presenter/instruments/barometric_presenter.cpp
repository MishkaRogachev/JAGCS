#include "barometric_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_traits.h"

using namespace presentation;

BarometricPresenter::BarometricPresenter(domain::TelemetryNode* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void BarometricPresenter::onParametersChanged(const domain::TelemetryMap& parameters)
{
    if (parameters.contains(domain::TelemetryId::Altitude))
        this->setViewProperty(PROPERTY(barometricAltitude),
                              parameters[domain::TelemetryId::Altitude]);
    if (parameters.contains(domain::TelemetryId::Climb))
        this->setViewProperty(PROPERTY(barometricClimb),
                              parameters[domain::TelemetryId::Climb]);
}
