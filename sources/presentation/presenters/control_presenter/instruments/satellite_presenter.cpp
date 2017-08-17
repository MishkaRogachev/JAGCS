#include "satellite_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

SatellitePresenter::SatellitePresenter(domain::Telemetry* node, QObject* parent):
    AbstractTelemetryPresenter(node, parent)
{}

void SatellitePresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Enabled))
        this->setViewsProperty(PROPERTY(satelliteEnabled), parameters[domain::Telemetry::Enabled]);
    if (parameters.contains(domain::Telemetry::Operational))
        this->setViewsProperty(PROPERTY(satelliteOperational), parameters[domain::Telemetry::Operational]);
    if (parameters.contains(domain::Telemetry::Fix))
        this->setViewsProperty(PROPERTY(fix), parameters[domain::Telemetry::Fix]);
    if (parameters.contains(domain::Telemetry::Coordinate))
        this->setViewsProperty(PROPERTY(coordinate), parameters[domain::Telemetry::Coordinate]);
    if (parameters.contains(domain::Telemetry::Groundspeed))
        this->setViewsProperty(PROPERTY(groundspeed), parameters[domain::Telemetry::Groundspeed]);
    if (parameters.contains(domain::Telemetry::Course))
        this->setViewsProperty(PROPERTY(course), parameters[domain::Telemetry::Course]);
    if (parameters.contains(domain::Telemetry::Altitude))
        this->setViewsProperty(PROPERTY(satelliteAltitude), parameters[domain::Telemetry::Altitude]);
    if (parameters.contains(domain::Telemetry::Eph))
        this->setViewsProperty(PROPERTY(eph), parameters[domain::Telemetry::Eph]);
    if (parameters.contains(domain::Telemetry::Epv))
        this->setViewsProperty(PROPERTY(epv), parameters[domain::Telemetry::Epv]);
    if (parameters.contains(domain::Telemetry::SatellitesVisible))
        this->setViewsProperty(PROPERTY(satellitesVisible), parameters[domain::Telemetry::SatellitesVisible]);
}
