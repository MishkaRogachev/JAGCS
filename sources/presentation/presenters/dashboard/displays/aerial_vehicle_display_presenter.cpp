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
                    std::bind(&AerialVehicleDisplayPresenter::updateEkf, this, std::placeholders::_1));

    this->chainNode(node->childNode(domain::Telemetry::Pitot),
                    std::bind(&AerialVehicleDisplayPresenter::updatePitot, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Barometric),
                    std::bind(&AerialVehicleDisplayPresenter::updateBarometric, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Radalt),
                    std::bind(&AerialVehicleDisplayPresenter::updateRadalt, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::FlightControl),
                    std::bind(&AerialVehicleDisplayPresenter::updateFlightControl, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Navigator),
                    std::bind(&AerialVehicleDisplayPresenter::updateNavigator, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Wind),
                    std::bind(&AerialVehicleDisplayPresenter::updateWind, this, std::placeholders::_1));
}

void AerialVehicleDisplayPresenter::updateEkf(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(ekf), PROPERTY(velocityVariance),
                             parameters.value(domain::Telemetry::VelocityVariance, 0.0));
    this->setVehicleProperty(PROPERTY(ekf), PROPERTY(verticalVariance),
                             parameters.value(domain::Telemetry::VerticalVariance, 0.0));
    this->setVehicleProperty(PROPERTY(ekf), PROPERTY(horizontVariance),
                             parameters.value(domain::Telemetry::HorizontVariance, 0.0));
    this->setVehicleProperty(PROPERTY(ekf), PROPERTY(compassVariance),
                             parameters.value(domain::Telemetry::CompassVariance, 0.0));
    this->setVehicleProperty(PROPERTY(ekf), PROPERTY(terrainAltitudeVariance),
                             parameters.value(domain::Telemetry::TerrainAltitudeVariance, 0.0));
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
                             parameters.value(domain::Telemetry::TrueAirspeed, 0));
    this->setVehicleProperty(PROPERTY(pitot), PROPERTY(indicatedAirspeed),
                             parameters.value(domain::Telemetry::IndicatedAirspeed, 0));
}

void AerialVehicleDisplayPresenter::updateBarometric(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(barometric), PROPERTY(present),
                             parameters.value(domain::Telemetry::Present, false));
    this->setVehicleProperty(PROPERTY(barometric), PROPERTY(enabled),
                             parameters.value(domain::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(barometric), PROPERTY(operational),
                             parameters.value(domain::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(barometric), PROPERTY(altitude),
                             parameters.value(domain::Telemetry::AltitudeMsl, 0));
    this->setVehicleProperty(PROPERTY(barometric), PROPERTY(climb),
                             parameters.value(domain::Telemetry::Climb, 0));
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
                             parameters.value(domain::Telemetry::Altitude, 0));
}

void AerialVehicleDisplayPresenter::updateFlightControl(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(flightControl), PROPERTY(desiredPitch),
                             parameters.value(domain::Telemetry::DesiredPitch, 0));
    this->setVehicleProperty(PROPERTY(flightControl), PROPERTY(desiredRoll),
                             parameters.value(domain::Telemetry::DesiredRoll, 0));
    this->setVehicleProperty(PROPERTY(flightControl), PROPERTY(desiredHeading),
                             parameters.value(domain::Telemetry::DesiredHeading, 0));
    this->setVehicleProperty(PROPERTY(navigator), PROPERTY(airspeedError),
                             parameters.value(domain::Telemetry::AirspeedError, false));
    this->setVehicleProperty(PROPERTY(navigator), PROPERTY(altitudeError),
                             parameters.value(domain::Telemetry::AltitudeError, false));
}

void AerialVehicleDisplayPresenter::updateNavigator(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(navigator), PROPERTY(targetBearing),
                             parameters.value(domain::Telemetry::TargetBearing, 0));
    this->setVehicleProperty(PROPERTY(navigator), PROPERTY(targetDistance),
                             parameters.value(domain::Telemetry::Distance, 0));
    this->setVehicleProperty(PROPERTY(navigator), PROPERTY(trackError),
                             parameters.value(domain::Telemetry::TrackError, 0));
}

void AerialVehicleDisplayPresenter::updateWind(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(wind), PROPERTY(direction),
                             parameters.value(domain::Telemetry::Yaw, false));
    this->setVehicleProperty(PROPERTY(wind), PROPERTY(speed),
                             parameters.value(domain::Telemetry::Speed, false));
}

