#include "aerial_vehicle_display_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "vibration_model.h"

using namespace presentation;

AerialVehicleDisplayPresenter::AerialVehicleDisplayPresenter(QObject* parent):
    BaseVehicleDisplayPresenter(parent)
{}

void AerialVehicleDisplayPresenter::connectNode(domain::Telemetry* node)
{
    BaseVehicleDisplayPresenter::connectNode(node);

    domain::Telemetry* ahrs = node->childNode(domain::Telemetry::Ahrs);
    this->chainNode(ahrs->childNode(domain::Telemetry::Ekf),
                    std::bind(&AerialVehicleDisplayPresenter::updateEkf,
                              this, std::placeholders::_1));

    this->chainNode(node->childNode(domain::Telemetry::Pitot),
                    std::bind(&AerialVehicleDisplayPresenter::updatePitot,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Barometric),
                    std::bind(&AerialVehicleDisplayPresenter::updateBarometric,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Radalt),
                    std::bind(&AerialVehicleDisplayPresenter::updateRadalt,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::FlightControl),
                    std::bind(&AerialVehicleDisplayPresenter::updateFlightControl,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Navigator),
                    std::bind(&AerialVehicleDisplayPresenter::updateNavigator,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::LandingSystem),
                    std::bind(&AerialVehicleDisplayPresenter::updateLandingSystem,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Wind),
                    std::bind(&AerialVehicleDisplayPresenter::updateWind,
                              this, std::placeholders::_1));
}

void AerialVehicleDisplayPresenter::updateEkf(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(ekf), PROPERTY(velocityVariance),
                             parameters.value(domain::Telemetry::VelocityVariance, qQNaN()));
    this->setVehicleProperty(PROPERTY(ekf), PROPERTY(verticalVariance),
                             parameters.value(domain::Telemetry::VerticalVariance, qQNaN()));
    this->setVehicleProperty(PROPERTY(ekf), PROPERTY(horizontVariance),
                             parameters.value(domain::Telemetry::HorizontVariance, qQNaN()));
    this->setVehicleProperty(PROPERTY(ekf), PROPERTY(compassVariance),
                             parameters.value(domain::Telemetry::CompassVariance, qQNaN()));
    this->setVehicleProperty(PROPERTY(ekf), PROPERTY(terrainAltitudeVariance),
                             parameters.value(domain::Telemetry::TerrainAltitudeVariance, qQNaN()));
}

void AerialVehicleDisplayPresenter::updatePitot(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(pitot), PROPERTY(present),
                             parameters.value(domain::Telemetry::Present, false));
    this->setVehicleProperty(PROPERTY(pitot), PROPERTY(enabled),
                             parameters.value(domain::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(pitot), PROPERTY(operational),
                             parameters.value(domain::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(pitot), PROPERTY(trueAirspeed),
                             parameters.value(domain::Telemetry::TrueAirspeed, qQNaN()));
    this->setVehicleProperty(PROPERTY(pitot), PROPERTY(indicatedAirspeed),
                             parameters.value(domain::Telemetry::IndicatedAirspeed, qQNaN()));
}

void AerialVehicleDisplayPresenter::updateBarometric(
        const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(barometric), PROPERTY(present),
                             parameters.value(domain::Telemetry::Present, false));
    this->setVehicleProperty(PROPERTY(barometric), PROPERTY(enabled),
                             parameters.value(domain::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(barometric), PROPERTY(operational),
                             parameters.value(domain::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(barometric), PROPERTY(altitude),
                             parameters.value(domain::Telemetry::AltitudeMsl, qQNaN()));
    this->setVehicleProperty(PROPERTY(barometric), PROPERTY(climb),
                             parameters.value(domain::Telemetry::Climb, qQNaN()));
}

void AerialVehicleDisplayPresenter::updateRadalt(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(radalt), PROPERTY(present),
                             parameters.value(domain::Telemetry::Present, false));
    this->setVehicleProperty(PROPERTY(radalt), PROPERTY(enabled),
                             parameters.value(domain::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(radalt), PROPERTY(operational),
                             parameters.value(domain::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(radalt), PROPERTY(altitude),
                             parameters.value(domain::Telemetry::Altitude, qQNaN()));
}

void AerialVehicleDisplayPresenter::updateFlightControl(
        const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(flightControl), PROPERTY(desiredPitch),
                             parameters.value(domain::Telemetry::DesiredPitch, qQNaN()));
    this->setVehicleProperty(PROPERTY(flightControl), PROPERTY(desiredRoll),
                             parameters.value(domain::Telemetry::DesiredRoll, qQNaN()));
    this->setVehicleProperty(PROPERTY(flightControl), PROPERTY(desiredHeading),
                             parameters.value(domain::Telemetry::DesiredHeading, qQNaN()));
    this->setVehicleProperty(PROPERTY(flightControl), PROPERTY(airspeedError),
                             parameters.value(domain::Telemetry::AirspeedError, qQNaN()));
    this->setVehicleProperty(PROPERTY(flightControl), PROPERTY(altitudeError),
                             parameters.value(domain::Telemetry::AltitudeError, qQNaN()));
}

void AerialVehicleDisplayPresenter::updateNavigator(
        const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(navigator), PROPERTY(targetBearing),
                             parameters.value(domain::Telemetry::TargetBearing, qQNaN()));
    this->setVehicleProperty(PROPERTY(navigator), PROPERTY(targetDistance),
                             parameters.value(domain::Telemetry::Distance, 0));
    this->setVehicleProperty(PROPERTY(navigator), PROPERTY(trackError),
                             parameters.value(domain::Telemetry::TrackError, qQNaN()));
}

void AerialVehicleDisplayPresenter::updateLandingSystem(
        const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(landingSystem), PROPERTY(distance),
                             parameters.value(domain::Telemetry::Distance, 0));
    this->setVehicleProperty(PROPERTY(landingSystem), PROPERTY(deviationX),
                             parameters.value(domain::Telemetry::DeviationX, qQNaN()));
    this->setVehicleProperty(PROPERTY(landingSystem), PROPERTY(deviationY),
                             parameters.value(domain::Telemetry::DeviationY, qQNaN()));
    this->setVehicleProperty(PROPERTY(landingSystem), PROPERTY(sizeX),
                             parameters.value(domain::Telemetry::SizeX, qQNaN()));
    this->setVehicleProperty(PROPERTY(landingSystem), PROPERTY(sizeY),
                             parameters.value(domain::Telemetry::SizeY, qQNaN()));
}

void AerialVehicleDisplayPresenter::updateWind(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(wind), PROPERTY(direction),
                             parameters.value(domain::Telemetry::Yaw, qQNaN()));
    this->setVehicleProperty(PROPERTY(wind), PROPERTY(speed),
                             parameters.value(domain::Telemetry::Speed, qQNaN()));
}

