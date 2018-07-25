#include "aerial_vehicle_display_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "vibration_model.h"

using namespace presentation;

AerialVehicleDisplayPresenter::AerialVehicleDisplayPresenter(QObject* parent):
    BaseVehicleDisplayPresenter(parent)
{}

void AerialVehicleDisplayPresenter::connectNode(data_source::Telemetry* node)
{
    BaseVehicleDisplayPresenter::connectNode(node);

    data_source::Telemetry* ahrs = node->childNode(data_source::Telemetry::Ahrs);
    this->chainNode(ahrs->childNode(data_source::Telemetry::Ekf),
                    std::bind(&AerialVehicleDisplayPresenter::updateEkf,
                              this, std::placeholders::_1));

    this->chainNode(node->childNode(data_source::Telemetry::Pitot),
                    std::bind(&AerialVehicleDisplayPresenter::updatePitot,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(data_source::Telemetry::Barometric),
                    std::bind(&AerialVehicleDisplayPresenter::updateBarometric,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(data_source::Telemetry::Radalt),
                    std::bind(&AerialVehicleDisplayPresenter::updateRadalt,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(data_source::Telemetry::FlightControl),
                    std::bind(&AerialVehicleDisplayPresenter::updateFlightControl,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(data_source::Telemetry::Navigator),
                    std::bind(&AerialVehicleDisplayPresenter::updateNavigator,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(data_source::Telemetry::LandingSystem),
                    std::bind(&AerialVehicleDisplayPresenter::updateLandingSystem,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(data_source::Telemetry::Wind),
                    std::bind(&AerialVehicleDisplayPresenter::updateWind,
                              this, std::placeholders::_1));
}

void AerialVehicleDisplayPresenter::updateEkf(const data_source::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(ekf), PROPERTY(velocityVariance),
                             parameters.value(data_source::Telemetry::VelocityVariance, qQNaN()));
    this->setVehicleProperty(PROPERTY(ekf), PROPERTY(verticalVariance),
                             parameters.value(data_source::Telemetry::VerticalVariance, qQNaN()));
    this->setVehicleProperty(PROPERTY(ekf), PROPERTY(horizontVariance),
                             parameters.value(data_source::Telemetry::HorizontVariance, qQNaN()));
    this->setVehicleProperty(PROPERTY(ekf), PROPERTY(compassVariance),
                             parameters.value(data_source::Telemetry::CompassVariance, qQNaN()));
    this->setVehicleProperty(PROPERTY(ekf), PROPERTY(terrainAltitudeVariance),
                             parameters.value(data_source::Telemetry::TerrainAltitudeVariance, qQNaN()));
}

void AerialVehicleDisplayPresenter::updatePitot(const data_source::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(pitot), PROPERTY(present),
                             parameters.value(data_source::Telemetry::Present, true));
    this->setVehicleProperty(PROPERTY(pitot), PROPERTY(enabled),
                             parameters.value(data_source::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(pitot), PROPERTY(operational),
                             parameters.value(data_source::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(pitot), PROPERTY(trueAirspeed),
                             parameters.value(data_source::Telemetry::TrueAirspeed, qQNaN()));
    this->setVehicleProperty(PROPERTY(pitot), PROPERTY(indicatedAirspeed),
                             parameters.value(data_source::Telemetry::IndicatedAirspeed, qQNaN()));
}

void AerialVehicleDisplayPresenter::updateBarometric(
        const data_source::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(barometric), PROPERTY(present),
                             parameters.value(data_source::Telemetry::Present, true));
    this->setVehicleProperty(PROPERTY(barometric), PROPERTY(enabled),
                             parameters.value(data_source::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(barometric), PROPERTY(operational),
                             parameters.value(data_source::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(barometric), PROPERTY(altitude),
                             parameters.value(data_source::Telemetry::AltitudeMsl, qQNaN()));
    this->setVehicleProperty(PROPERTY(barometric), PROPERTY(climb),
                             parameters.value(data_source::Telemetry::Climb, qQNaN()));
}

void AerialVehicleDisplayPresenter::updateRadalt(const data_source::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(radalt), PROPERTY(present),
                             parameters.value(data_source::Telemetry::Present, true));
    this->setVehicleProperty(PROPERTY(radalt), PROPERTY(enabled),
                             parameters.value(data_source::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(radalt), PROPERTY(operational),
                             parameters.value(data_source::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(radalt), PROPERTY(altitude),
                             parameters.value(data_source::Telemetry::Altitude, qQNaN()));
}

void AerialVehicleDisplayPresenter::updateFlightControl(
        const data_source::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(flightControl), PROPERTY(desiredPitch),
                             parameters.value(data_source::Telemetry::DesiredPitch, qQNaN()));
    this->setVehicleProperty(PROPERTY(flightControl), PROPERTY(desiredRoll),
                             parameters.value(data_source::Telemetry::DesiredRoll, qQNaN()));
    this->setVehicleProperty(PROPERTY(flightControl), PROPERTY(desiredHeading),
                             parameters.value(data_source::Telemetry::DesiredHeading, qQNaN()));
    this->setVehicleProperty(PROPERTY(flightControl), PROPERTY(airspeedError),
                             parameters.value(data_source::Telemetry::AirspeedError, qQNaN()));
    this->setVehicleProperty(PROPERTY(flightControl), PROPERTY(altitudeError),
                             parameters.value(data_source::Telemetry::AltitudeError, qQNaN()));
}

void AerialVehicleDisplayPresenter::updateNavigator(
        const data_source::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(navigator), PROPERTY(targetBearing),
                             parameters.value(data_source::Telemetry::TargetBearing, qQNaN()));
    this->setVehicleProperty(PROPERTY(navigator), PROPERTY(targetDistance),
                             parameters.value(data_source::Telemetry::Distance, 0));
    this->setVehicleProperty(PROPERTY(navigator), PROPERTY(trackError),
                             parameters.value(data_source::Telemetry::TrackError, qQNaN()));
}

void AerialVehicleDisplayPresenter::updateLandingSystem(
        const data_source::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(landingSystem), PROPERTY(distance),
                             parameters.value(data_source::Telemetry::Distance, 0));
    this->setVehicleProperty(PROPERTY(landingSystem), PROPERTY(deviationX),
                             parameters.value(data_source::Telemetry::DeviationX, qQNaN()));
    this->setVehicleProperty(PROPERTY(landingSystem), PROPERTY(deviationY),
                             parameters.value(data_source::Telemetry::DeviationY, qQNaN()));
    this->setVehicleProperty(PROPERTY(landingSystem), PROPERTY(sizeX),
                             parameters.value(data_source::Telemetry::SizeX, qQNaN()));
    this->setVehicleProperty(PROPERTY(landingSystem), PROPERTY(sizeY),
                             parameters.value(data_source::Telemetry::SizeY, qQNaN()));
}

void AerialVehicleDisplayPresenter::updateWind(const data_source::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(wind), PROPERTY(direction),
                             parameters.value(data_source::Telemetry::Yaw, qQNaN()));
    this->setVehicleProperty(PROPERTY(wind), PROPERTY(speed),
                             parameters.value(data_source::Telemetry::Speed, qQNaN()));
}

