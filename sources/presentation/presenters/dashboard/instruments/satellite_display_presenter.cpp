#include "satellite_display_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

SatelliteDisplayPresenter::SatelliteDisplayPresenter(QObject* parent):
    AbstractInstrumentPresenter(parent)
{}

void SatelliteDisplayPresenter::connectNode(domain::Telemetry* node)
{
    this->chainNode(node->childNode(domain::Telemetry::Satellite),
                    std::bind(&SatelliteDisplayPresenter::updateSatellite, this, std::placeholders::_1));
}

void SatelliteDisplayPresenter::updateSatellite(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(satelliteEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(satelliteOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(fix), parameters.value(domain::Telemetry::Fix, 0));
    this->setViewProperty(PROPERTY(coordinate), parameters.value(domain::Telemetry::Coordinate, 0));
    this->setViewProperty(PROPERTY(eph), parameters.value(domain::Telemetry::Eph, 0));
    this->setViewProperty(PROPERTY(epv), parameters.value(domain::Telemetry::Epv, 0));
    this->setViewProperty(PROPERTY(satellitesVisible), parameters.value(domain::Telemetry::SatellitesVisible, 0));
}
