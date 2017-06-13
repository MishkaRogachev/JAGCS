#include "generic_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_traits.h"

using namespace presentation;

GenericPresenter::GenericPresenter(domain::TelemetryNode* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void GenericPresenter::onParametersChanged(const QVariantMap& parameters)
{
    for (const QString& key: parameters.keys())
    {
        if (key == telemetry::online)
            this->setViewProperty(PROPERTY(online), parameters[key]);
        else if (key == telemetry::armed)
            this->setViewProperty(PROPERTY(armed), parameters[key]);
        else if (key == telemetry::mode)
            this->setViewProperty(PROPERTY(mode), parameters[key]);
    }
}
