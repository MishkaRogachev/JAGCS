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
    for (const QString& key: parameters.keys())
    {
        if (key == telemetry::altitude) this->setViewProperty(PROPERTY(barometricAltitude), parameters[key]);
        if (key == telemetry::climb) this->setViewProperty(PROPERTY(barometricClimb), parameters[key]);
    }
}
