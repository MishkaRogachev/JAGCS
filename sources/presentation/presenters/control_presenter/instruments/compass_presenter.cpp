#include "compass_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

CompassPresenter::CompassPresenter(domain::Telemetry* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void CompassPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Heading))
        this->setViewProperty(PROPERTY(heading), parameters[domain::Telemetry::Heading]);
}
