#include "compass_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_traits.h"

using namespace presentation;

CompassPresenter::CompassPresenter(domain::TelemetryNode* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void CompassPresenter::onParametersChanged(const domain::TelemetryMap& parameters)
{
    if (parameters.contains(domain::TelemetryId::Heading))
        this->setViewProperty(PROPERTY(heading), parameters[domain::TelemetryId::Heading]);
}
