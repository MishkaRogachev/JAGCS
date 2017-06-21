#include "battery_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

BatteryPresenter::BatteryPresenter(domain::Telemetry* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void BatteryPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Voltage))
        this->setViewProperty(PROPERTY(batteryVoltage), parameters[domain::Telemetry::Voltage]);
    if (parameters.contains(domain::Telemetry::Current))
        this->setViewProperty(PROPERTY(batteryCurrent), parameters[domain::Telemetry::Current]);
    if (parameters.contains(domain::Telemetry::Percentage))
        this->setViewProperty(PROPERTY(batteryPercentage), parameters[domain::Telemetry::Percentage]);
}
