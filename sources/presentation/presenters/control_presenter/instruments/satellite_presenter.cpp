#include "satellite_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

SatellitePresenter::SatellitePresenter(domain::Telemetry* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void SatellitePresenter::onParametersChanged(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Enabled))
        this->setViewProperty(PROPERTY(satelliteEnabled),
                              parameters[domain::Telemetry::Enabled]);
    if (parameters.contains(domain::Telemetry::Operational))
        this->setViewProperty(PROPERTY(satelliteOperational),
                              parameters[domain::Telemetry::Operational]);
    if (parameters.contains(domain::Telemetry::Fix))
        this->setViewProperty(PROPERTY(fix),
                              parameters[domain::Telemetry::Fix]);
    if (parameters.contains(domain::Telemetry::Coordinate))
        this->setViewProperty(PROPERTY(coordinate),
                              parameters[domain::Telemetry::Coordinate]);
    if (parameters.contains(domain::Telemetry::Groundspeed))
        this->setViewProperty(PROPERTY(groundspeed),
                              parameters[domain::Telemetry::Groundspeed]);
    if (parameters.contains(domain::Telemetry::Course))
        this->setViewProperty(PROPERTY(course),
                              parameters[domain::Telemetry::Course]);
    if (parameters.contains(domain::Telemetry::Altitude))
        this->setViewProperty(PROPERTY(satelliteAltitude),
                              parameters[domain::Telemetry::Altitude]);
    if (parameters.contains(domain::Telemetry::Eph))
        this->setViewProperty(PROPERTY(eph),
                              parameters[domain::Telemetry::Eph]);
    if (parameters.contains(domain::Telemetry::Epv))
        this->setViewProperty(PROPERTY(epv),
                              parameters[domain::Telemetry::Epv]);
    if (parameters.contains(domain::Telemetry::SatellitesVisible))
        this->setViewProperty(PROPERTY(satellitesVisible),
                              parameters[domain::Telemetry::SatellitesVisible]);
}
