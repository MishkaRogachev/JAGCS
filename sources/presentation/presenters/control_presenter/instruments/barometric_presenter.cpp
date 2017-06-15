#include "barometric_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

BarometricPresenter::BarometricPresenter(domain::Telemetry* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void BarometricPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Altitude))
        this->setViewProperty(PROPERTY(barometricAltitude),
                              parameters[domain::Telemetry::Altitude]);
    if (parameters.contains(domain::Telemetry::Climb))
        this->setViewProperty(PROPERTY(barometricClimb),
                              parameters[domain::Telemetry::Climb]);
}
