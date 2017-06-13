#include "satellite_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_traits.h"

using namespace presentation;

SatellitePresenter::SatellitePresenter(domain::TelemetryNode* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void SatellitePresenter::onParametersChanged(const QVariantMap& parameters)
{
    if (parameters.contains(telemetry::fix))
        this->setViewProperty(PROPERTY(fix), parameters[telemetry::fix]);
    if (parameters.contains(telemetry::groundspeed))
        this->setViewProperty(PROPERTY(groundspeed), parameters[telemetry::groundspeed]);
    if (parameters.contains(telemetry::course))
        this->setViewProperty(PROPERTY(course), parameters[telemetry::course]);
    if (parameters.contains(telemetry::altitude))
        this->setViewProperty(PROPERTY(satelliteAltitude), parameters[telemetry::altitude]);
    if (parameters.contains(telemetry::eph))
        this->setViewProperty(PROPERTY(eph), parameters[telemetry::eph]);
    if (parameters.contains(telemetry::epv))
        this->setViewProperty(PROPERTY(epv), parameters[telemetry::epv]);
    if (parameters.contains(telemetry::satellitesVisible))
        this->setViewProperty(PROPERTY(satellitesVisible), parameters[telemetry::satellitesVisible]);
}
