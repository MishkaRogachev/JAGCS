#include "compass_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_traits.h"

using namespace presentation;

CompassPresenter::CompassPresenter(domain::TelemetryNode* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void CompassPresenter::onParametersChanged(const QVariantMap& parameters)
{
    if (parameters.contains(telemetry::heading))
        this->setViewProperty(PROPERTY(heading), parameters[telemetry::heading]);
}
