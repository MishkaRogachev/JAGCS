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
    this->chainNode(node->childNode(domain::Telemetry::Navigator),
                    std::bind(&FlightDisplayPresenter::updateNavigator, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::HomePosition),
                    std::bind(&FlightDisplayPresenter::updateHomeAltitude, this, std::placeholders::_1));
}

void FlightDisplayPresenter::updateStatus(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(armed), parameters.value(domain::Telemetry::Armed));
    this->setViewProperty(PROPERTY(guided), parameters.value(domain::Telemetry::Guided));
}

void FlightDisplayPresenter::updateAhrs(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(ahrsEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(ahrsOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(pitch), parameters.value(domain::Telemetry::Pitch, 0));
    this->setViewProperty(PROPERTY(roll), parameters.value(domain::Telemetry::Roll, 0));
    this->setViewProperty(PROPERTY(yaw), parameters.value(domain::Telemetry::Yaw, 0));
    this->setViewProperty(PROPERTY(yawspeed), parameters.value(domain::Telemetry::YawSpeed, 0));
}

void FlightDisplayPresenter::updateSatellite(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(satelliteEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(satelliteOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(fix), parameters.value(domain::Telemetry::Fix, 0));
    this->setViewProperty(PROPERTY(coordinate), parameters.value(domain::Telemetry::Coordinate, 0));
    this->setViewProperty(PROPERTY(groundspeed), parameters.value(domain::Telemetry::Groundspeed, 0));
    this->setViewProperty(PROPERTY(course), parameters.value(domain::Telemetry::Course, 0));
    this->setViewProperty(PROPERTY(satelliteAltitude), parameters.value(domain::Telemetry::Altitude, 0));
    this->setViewProperty(PROPERTY(eph), parameters.value(domain::Telemetry::Eph, 0));
    this->setViewProperty(PROPERTY(epv), parameters.value(domain::Telemetry::Epv, 0));
    this->setViewProperty(PROPERTY(satellitesVisible), parameters.value(domain::Telemetry::SatellitesVisible, 0));
}

void FlightDisplayPresenter::updatePowerSystem(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(throttle), parameters.value(domain::Telemetry::Throttle, 0));
}

void FlightDisplayPresenter::updatePitot(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(pitotEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(pitotOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(trueAirspeed), parameters.value(domain::Telemetry::TrueAirspeed, 0));
    this->setViewProperty(PROPERTY(indicatedAirspeed), parameters.value(domain::Telemetry::IndicatedAirspeed, 0));
}

void FlightDisplayPresenter::updateBarometric(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(barometricEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(barometricOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(barometricAltitude), parameters.value(domain::Telemetry::Altitude, 0));
    this->setViewProperty(PROPERTY(barometricClimb), parameters.value(domain::Telemetry::Climb, 0));
}

void FlightDisplayPresenter::updateRangefinder(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(rangefinderEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(rangefinderOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(rangefinderHeight), parameters.value(domain::Telemetry::Height, 0));
}

void FlightDisplayPresenter::updateNavigator(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(desiredPitch), parameters.value(domain::Telemetry::DesiredPitch, 0));
    this->setViewProperty(PROPERTY(desiredRoll), parameters.value(domain::Telemetry::DesiredRoll, 0));
    this->setViewProperty(PROPERTY(airspeedError), parameters.value(domain::Telemetry::AirspeedError, false));
    this->setViewProperty(PROPERTY(altitudeError), parameters.value(domain::Telemetry::AltitudeError, false));
}

void FlightDisplayPresenter::updateHomeAltitude(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(homeAltitude), parameters.value(domain::Telemetry::Altitude, 0));
}
