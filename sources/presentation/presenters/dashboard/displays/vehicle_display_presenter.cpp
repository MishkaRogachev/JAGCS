#include "vehicle_display_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

VehicleDisplayPresenter::VehicleDisplayPresenter(QObject* parent):
    CommonVehicleDisplayPresenter(parent)
{}

void VehicleDisplayPresenter::connectNode(domain::Telemetry* node)
{
    CommonVehicleDisplayPresenter::connectNode(node);

    this->chainNode(node->childNode(domain::Telemetry::Status),
                    std::bind(&VehicleDisplayPresenter::updateStatus, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Ahrs),
                    std::bind(&VehicleDisplayPresenter::updateAhrs, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Compass),
                    std::bind(&VehicleDisplayPresenter::updateCompass, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Satellite),
                    std::bind(&VehicleDisplayPresenter::updateSatellite, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::PowerSystem),
                    std::bind(&VehicleDisplayPresenter::updatePowerSystem, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Pitot),
                    std::bind(&VehicleDisplayPresenter::updatePitot, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Barometric),
                    std::bind(&VehicleDisplayPresenter::updateBarometric, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::HomePosition),
                    std::bind(&VehicleDisplayPresenter::updateHome, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Rangefinder),
                    std::bind(&VehicleDisplayPresenter::updateRangefinder, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Position),
                    std::bind(&VehicleDisplayPresenter::updatePosition, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Navigator),
                    std::bind(&VehicleDisplayPresenter::updateNavigator, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Wind),
                    std::bind(&VehicleDisplayPresenter::updateWind, this, std::placeholders::_1));
}

void VehicleDisplayPresenter::updateStatus(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(armed), parameters.value(domain::Telemetry::Armed));
    this->setViewProperty(PROPERTY(guided), parameters.value(domain::Telemetry::Guided));
}

void VehicleDisplayPresenter::updateAhrs(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(ahrsEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(ahrsOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(pitch), parameters.value(domain::Telemetry::Pitch, 0));
    this->setViewProperty(PROPERTY(roll), parameters.value(domain::Telemetry::Roll, 0));
    this->setViewProperty(PROPERTY(yaw), parameters.value(domain::Telemetry::Yaw, 0));
    this->setViewProperty(PROPERTY(yawspeed), parameters.value(domain::Telemetry::YawSpeed, 0));
}

void VehicleDisplayPresenter::updateCompass(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(compassEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(compassOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(heading), parameters.value(domain::Telemetry::Heading, 0));
}

void VehicleDisplayPresenter::updateSatellite(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(satelliteEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(satelliteOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(fix), parameters.value(domain::Telemetry::Fix, 0));
    this->setViewProperty(PROPERTY(course), parameters.value(domain::Telemetry::Course, 0));
    this->setViewProperty(PROPERTY(groundspeed), parameters.value(domain::Telemetry::Groundspeed, 0));
    this->setViewProperty(PROPERTY(coordinate), parameters.value(domain::Telemetry::Coordinate, 0));
    this->setViewProperty(PROPERTY(satelliteAltitude), parameters.value(domain::Telemetry::Altitude, 0));
    this->setViewProperty(PROPERTY(eph), parameters.value(domain::Telemetry::Eph, 0));
    this->setViewProperty(PROPERTY(epv), parameters.value(domain::Telemetry::Epv, 0));
    this->setViewProperty(PROPERTY(satellitesVisible), parameters.value(domain::Telemetry::SatellitesVisible, 0));
}

void VehicleDisplayPresenter::updatePowerSystem(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(throttle), parameters.value(domain::Telemetry::Throttle, 0));
}

void VehicleDisplayPresenter::updatePitot(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(pitotPresent), parameters.value(domain::Telemetry::Present, false));
    this->setViewProperty(PROPERTY(pitotEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(pitotOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(trueAirspeed), parameters.value(domain::Telemetry::TrueAirspeed, 0));
    this->setViewProperty(PROPERTY(indicatedAirspeed), parameters.value(domain::Telemetry::IndicatedAirspeed, 0));
}

void VehicleDisplayPresenter::updateBarometric(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(barometricEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(barometricOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(barometricAltitude), parameters.value(domain::Telemetry::AltitudeMsl, 0));
    this->setViewProperty(PROPERTY(barometricClimb), parameters.value(domain::Telemetry::Climb, 0));
}

void VehicleDisplayPresenter::updateRangefinder(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(rangefinderEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(rangefinderOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(rangefinderHeight), parameters.value(domain::Telemetry::Height, 0));
}

void VehicleDisplayPresenter::updatePosition(const domain::Telemetry::TelemetryMap& parameters)
{
    m_position = parameters.value(domain::Telemetry::Coordinate).value<QGeoCoordinate>();

    this->updateHoming();
}

void VehicleDisplayPresenter::updateHome(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(homeAltitude), parameters.value(domain::Telemetry::Altitude, 0));

    m_homePosition = parameters.value(domain::Telemetry::Coordinate).value<QGeoCoordinate>();
    this->updateHoming();
}

void VehicleDisplayPresenter::updateNavigator(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(desiredPitch), parameters.value(domain::Telemetry::DesiredPitch, 0));
    this->setViewProperty(PROPERTY(desiredRoll), parameters.value(domain::Telemetry::DesiredRoll, 0));
    this->setViewProperty(PROPERTY(airspeedError), parameters.value(domain::Telemetry::AirspeedError, false));
    this->setViewProperty(PROPERTY(altitudeError), parameters.value(domain::Telemetry::AltitudeError, false));
    this->setViewProperty(PROPERTY(targetBearing), parameters.value(domain::Telemetry::TargetBearing, 0));
    this->setViewProperty(PROPERTY(desiredHeading), parameters.value(domain::Telemetry::DesiredHeading, 0));
    this->setViewProperty(PROPERTY(targetDistance), parameters.value(domain::Telemetry::TargetDistance, 0));
    this->setViewProperty(PROPERTY(trackError), parameters.value(domain::Telemetry::TrackError, 0));
}

void VehicleDisplayPresenter::updateWind(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(windDirection), parameters.value(domain::Telemetry::Yaw, false));
    this->setViewProperty(PROPERTY(windSpeed), parameters.value(domain::Telemetry::Speed, false));
}

void VehicleDisplayPresenter::updateHoming()
{
    if (m_position.isValid() && m_homePosition.isValid())
    {
        this->setViewProperty(PROPERTY(homeDistance), m_position.distanceTo(m_homePosition));
        this->setViewProperty(PROPERTY(homeDirection), m_position.azimuthTo(m_homePosition));
    }
    else
    {
        this->setViewProperty(PROPERTY(homeDistance), 0);
        this->setViewProperty(PROPERTY(homeDirection), 0);
    }
}
