#include "satellite_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_traits.h"

using namespace presentation;

SatellitePresenter::SatellitePresenter(domain::TelemetryNode* node, QObject* parent):
    AbstractInstrumentPresenter(node, parent)
{}

void SatellitePresenter::onParametersChanged(const domain::TelemetryMap& parameters)
{
    if (parameters.contains(domain::TelemetryId::Fix))
        this->setViewProperty(PROPERTY(fix),
                              parameters[domain::TelemetryId::Fix]);
    if (parameters.contains(domain::TelemetryId::Groundspeed))
        this->setViewProperty(PROPERTY(groundspeed),
                              parameters[domain::TelemetryId::Groundspeed]);
    if (parameters.contains(domain::TelemetryId::Course))
        this->setViewProperty(PROPERTY(course),
                              parameters[domain::TelemetryId::Course]);
    if (parameters.contains(domain::TelemetryId::Altitude))
        this->setViewProperty(PROPERTY(satelliteAltitude),
                              parameters[domain::TelemetryId::Altitude]);
    if (parameters.contains(domain::TelemetryId::Eph))
        this->setViewProperty(PROPERTY(eph),
                              parameters[domain::TelemetryId::Eph]);
    if (parameters.contains(domain::TelemetryId::Epv))
        this->setViewProperty(PROPERTY(epv),
                              parameters[domain::TelemetryId::Epv]);
    if (parameters.contains(domain::TelemetryId::SatellitesVisible))
        this->setViewProperty(PROPERTY(satellitesVisible),
                              parameters[domain::TelemetryId::SatellitesVisible]);
}
