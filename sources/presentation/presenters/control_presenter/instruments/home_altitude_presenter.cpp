#include "home_altitude_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

HomeAltitudePresenter::HomeAltitudePresenter(domain::Telemetry* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void HomeAltitudePresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Altitude))
        this->setViewProperty(PROPERTY(homeAltitude), parameters[domain::Telemetry::Altitude]);
}
