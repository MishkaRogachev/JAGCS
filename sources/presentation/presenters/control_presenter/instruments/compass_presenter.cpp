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
    for (const QString& key: parameters.keys())
    {
        if (key == telemetry::heading)
            this->setViewProperty(PROPERTY(heading), parameters[key]);
    }
}
