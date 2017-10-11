#include "status_presenter.h"

//Internal
#include "modes.h"

// Qt
#include <QDebug>

using namespace presentation;

StatusPresenter::StatusPresenter(domain::Telemetry* node, QObject* parent):
    AbstractTelemetryPresenter(node, parent)
{}

void StatusPresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Armed))
        this->setViewsProperty(PROPERTY(armed), parameters[domain::Telemetry::Armed]);
    if (parameters.contains(domain::Telemetry::Auto))
        this->setViewsProperty(PROPERTY(automatic), parameters[domain::Telemetry::Auto]);
    if (parameters.contains(domain::Telemetry::Guided))
        this->setViewsProperty(PROPERTY(guided), parameters[domain::Telemetry::Guided]);
    if (parameters.contains(domain::Telemetry::Stabilized))
        this->setViewsProperty(PROPERTY(stabilized), parameters[domain::Telemetry::Stabilized]);
    if (parameters.contains(domain::Telemetry::Manual))
        this->setViewsProperty(PROPERTY(manual), parameters[domain::Telemetry::Manual]);

    if (parameters.contains(domain::Telemetry::AvailableModes))
    {
        QVariantList list;
        for (auto item: parameters[domain::Telemetry::AvailableModes].value< QList<domain::Mode> >())
        {
            list.append(QVariant::fromValue(item));
        }
        this->setViewsProperty(PROPERTY(availableModes), list);
    }
    if (parameters.contains(domain::Telemetry::Mode))
        this->setViewsProperty(PROPERTY(mode), parameters[domain::Telemetry::Mode]);
}
