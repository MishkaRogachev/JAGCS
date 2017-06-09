#include "artificial_horizon_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_traits.h"

using namespace presentation;

ArtificialHorizonPresenter::ArtificialHorizonPresenter(QObject* parent):
    AbstractInstrumentPresenter(parent)
{}

void ArtificialHorizonPresenter::applyParameters(const QVariantMap& parameters)
{
    for (const QString& key: parameters.keys())
    {
        if (key.endsWith(telemetry::pitch)) this->setViewProperty(PROPERTY(pitch), parameters[key]);
        if (key.endsWith(telemetry::roll)) this->setViewProperty(PROPERTY(roll), parameters[key]);
        if (key.endsWith(telemetry::yaw)) this->setViewProperty(PROPERTY(yaw), parameters[key]);
    }
}
