#include "flight_display_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

FlightDisplayPresenter::FlightDisplayPresenter(QObject* parent):
    AbstractInstrumentPresenter(parent)
{}

void FlightDisplayPresenter::connectNode(domain::Telemetry* node)
{
    this->chainNode(node->childNode(domain::Telemetry::Ahrs),
                    std::bind(&FlightDisplayPresenter::updateAhrs, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Satellite),
                    std::bind(&FlightDisplayPresenter::updateSatellite, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::PowerSystem),
                    std::bind(&FlightDisplayPresenter::updatePowerSystem, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Pitot),
                    std::bind(&FlightDisplayPresenter::updatePitot, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Barometric),
                    std::bind(&FlightDisplayPresenter::updateBarometric, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Rangefinder),
                    std::bind(&FlightDisplayPresenter::updateRangefinder, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::HomePosition),
                    std::bind(&FlightDisplayPresenter::updateHomeAltitude, this, std::placeholders::_1));
}

void FlightDisplayPresenter::updateAhrs(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Enabled))
        this->setViewProperty(PROPERTY(ahrsEnabled), parameters[domain::Telemetry::Enabled]);
    if (parameters.contains(domain::Telemetry::Operational))
        this->setViewProperty(PROPERTY(ahrsOperational), parameters[domain::Telemetry::Operational]);
    if (parameters.contains(domain::Telemetry::Pitch))
        this->setViewProperty(PROPERTY(pitch), parameters[domain::Telemetry::Pitch]);
    if (parameters.contains(domain::Telemetry::Roll))
        this->setViewProperty(PROPERTY(roll), parameters[domain::Telemetry::Roll]);
    if (parameters.contains(domain::Telemetry::Yaw))
        this->setViewProperty(PROPERTY(yaw), parameters[domain::Telemetry::Yaw]);
    if (parameters.contains(domain::Telemetry::YawSpeed))
        this->setViewProperty(PROPERTY(yawspeed), parameters[domain::Telemetry::YawSpeed]);
}

void FlightDisplayPresenter::updateSatellite(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Enabled))
        this->setViewProperty(PROPERTY(satelliteEnabled), parameters[domain::Telemetry::Enabled]);
    if (parameters.contains(domain::Telemetry::Operational))
        this->setViewProperty(PROPERTY(satelliteOperational), parameters[domain::Telemetry::Operational]);
    if (parameters.contains(domain::Telemetry::Fix))
        this->setViewProperty(PROPERTY(fix), parameters[domain::Telemetry::Fix]);
    if (parameters.contains(domain::Telemetry::Coordinate))
        this->setViewProperty(PROPERTY(coordinate), parameters[domain::Telemetry::Coordinate]);
    if (parameters.contains(domain::Telemetry::Groundspeed))
        this->setViewProperty(PROPERTY(groundspeed), parameters[domain::Telemetry::Groundspeed]);
    if (parameters.contains(domain::Telemetry::Course))
        this->setViewProperty(PROPERTY(course), parameters[domain::Telemetry::Course]);
    if (parameters.contains(domain::Telemetry::Altitude))
        this->setViewProperty(PROPERTY(satelliteAltitude), parameters[domain::Telemetry::Altitude]);
    if (parameters.contains(domain::Telemetry::Eph))
        this->setViewProperty(PROPERTY(eph), parameters[domain::Telemetry::Eph]);
    if (parameters.contains(domain::Telemetry::Epv))
        this->setViewProperty(PROPERTY(epv), parameters[domain::Telemetry::Epv]);
    if (parameters.contains(domain::Telemetry::SatellitesVisible))
        this->setViewProperty(PROPERTY(satellitesVisible), parameters[domain::Telemetry::SatellitesVisible]);
}

void FlightDisplayPresenter::updatePowerSystem(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Throttle))
        this->setViewProperty(PROPERTY(throttle), parameters[domain::Telemetry::Throttle]);
}

void FlightDisplayPresenter::updatePitot(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Enabled))
        this->setViewProperty(PROPERTY(pitotEnabled), parameters[domain::Telemetry::Enabled]);
    if (parameters.contains(domain::Telemetry::Operational))
        this->setViewProperty(PROPERTY(pitotOperational), parameters[domain::Telemetry::Operational]);
    if (parameters.contains(domain::Telemetry::TrueAirspeed))
        this->setViewProperty(PROPERTY(trueAirspeed), parameters[domain::Telemetry::TrueAirspeed]);
    if (parameters.contains(domain::Telemetry::IndicatedAirspeed))
        this->setViewProperty(PROPERTY(indicatedAirspeed), parameters[domain::Telemetry::IndicatedAirspeed]);
}

void FlightDisplayPresenter::updateBarometric(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Enabled))
        this->setViewProperty(PROPERTY(barometricEnabled), parameters[domain::Telemetry::Enabled]);
    if (parameters.contains(domain::Telemetry::Operational))
        this->setViewProperty(PROPERTY(barometricOperational), parameters[domain::Telemetry::Operational]);
    if (parameters.contains(domain::Telemetry::Altitude))
        this->setViewProperty(PROPERTY(barometricAltitude), parameters[domain::Telemetry::Altitude]);
    if (parameters.contains(domain::Telemetry::Climb))
        this->setViewProperty(PROPERTY(barometricClimb), parameters[domain::Telemetry::Climb]);
}

void FlightDisplayPresenter::updateRangefinder(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Enabled))
        this->setViewProperty(PROPERTY(rangefinderEnabled), parameters[domain::Telemetry::Enabled]);
    if (parameters.contains(domain::Telemetry::Operational))
        this->setViewProperty(PROPERTY(rangefinderOperational), parameters[domain::Telemetry::Operational]);
    if (parameters.contains(domain::Telemetry::Height))
        this->setViewProperty(PROPERTY(rangefinderHeight), parameters[domain::Telemetry::Height]);
}

void FlightDisplayPresenter::updateHomeAltitude(const domain::Telemetry::TelemetryMap& parameters)
{
    if (parameters.contains(domain::Telemetry::Altitude))
        this->setViewProperty(PROPERTY(homeAltitude), parameters[domain::Telemetry::Altitude]);
}
