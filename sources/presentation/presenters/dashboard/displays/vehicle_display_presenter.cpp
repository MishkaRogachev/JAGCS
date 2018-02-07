#include "vehicle_display_presenter.h"

// Qt
#include <QTime>
#include <QVector3D>
#include <QGeoCoordinate>
#include <QDebug>

// Internal
#include "vibration_model.h"

using namespace presentation;

VehicleDisplayPresenter::VehicleDisplayPresenter(QObject* parent):
    CommonVehicleDisplayPresenter(parent),
    m_vibrationModel(new VibrationModel(this))
{}

void VehicleDisplayPresenter::connectNode(domain::Telemetry* node)
{
    CommonVehicleDisplayPresenter::connectNode(node);

    domain::Telemetry* ahrs = node->childNode(domain::Telemetry::Ahrs);
    this->chainNode(ahrs, std::bind(&VehicleDisplayPresenter::updateAhrs, this, std::placeholders::_1));
    this->chainNode(ahrs->childNode(domain::Telemetry::Compass),
                    std::bind(&VehicleDisplayPresenter::updateCompass, this, std::placeholders::_1));
    this->chainNode(ahrs->childNode(domain::Telemetry::Ekf),
                    std::bind(&VehicleDisplayPresenter::updateEkf, this, std::placeholders::_1));

    this->chainNode(node->childNode(domain::Telemetry::Satellite),
                    std::bind(&VehicleDisplayPresenter::updateSatellite, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::PowerSystem),
                    std::bind(&VehicleDisplayPresenter::updatePowerSystem, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Battery),
                    std::bind(&VehicleDisplayPresenter::updateBattery, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Pitot),
                    std::bind(&VehicleDisplayPresenter::updatePitot, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Barometric),
                    std::bind(&VehicleDisplayPresenter::updateBarometric, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::HomePosition),
                    std::bind(&VehicleDisplayPresenter::updateHome, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Radalt),
                    std::bind(&VehicleDisplayPresenter::updateRadalt, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Position),
                    std::bind(&VehicleDisplayPresenter::updatePosition, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::FlightControl),
                    std::bind(&VehicleDisplayPresenter::updateFlightControl, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Navigator),
                    std::bind(&VehicleDisplayPresenter::updateNavigator, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Wind),
                    std::bind(&VehicleDisplayPresenter::updateWind, this, std::placeholders::_1));
}

void VehicleDisplayPresenter::updateAhrs(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(present),
                             parameters.value(domain::Telemetry::Present, false));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(enabled),
                             parameters.value(domain::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(operational),
                             parameters.value(domain::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(pitch),
                             parameters.value(domain::Telemetry::Pitch, 0));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(roll),
                             parameters.value(domain::Telemetry::Roll, 0));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(yaw),
                             parameters.value(domain::Telemetry::Yaw, 0));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(yawspeed),
                             parameters.value(domain::Telemetry::YawSpeed, 0));

    // TODO: telemetry timestamp
    Vibration vibration;
    vibration.timestamp = QTime::currentTime().msecsSinceStartOfDay();
    vibration.data = parameters.value(domain::Telemetry::Vibration).value<QVector3D>();

    m_vibrationModel->addData(vibration);
}

void VehicleDisplayPresenter::updateCompass(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(compass), PROPERTY(present),
                             parameters.value(domain::Telemetry::Present, false));
    this->setVehicleProperty(PROPERTY(compass), PROPERTY(enabled),
                             parameters.value(domain::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(compass), PROPERTY(operational),
                             parameters.value(domain::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(compass), PROPERTY(heading),
                             parameters.value(domain::Telemetry::Heading, 0));
}

void VehicleDisplayPresenter::updateEkf(const domain::Telemetry::TelemetryMap& parameters)
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

void VehicleDisplayPresenter::updateSatellite(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(present),
                             parameters.value(domain::Telemetry::Present, false));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(enabled),
                             parameters.value(domain::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(operational),
                             parameters.value(domain::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(fix),
                             parameters.value(domain::Telemetry::Fix, 0));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(course),
                             parameters.value(domain::Telemetry::Course, 0));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(groundspeed),
                             parameters.value(domain::Telemetry::Groundspeed, 0));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(coordinate),
                             parameters.value(domain::Telemetry::Coordinate, 0));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(altitude),
                             parameters.value(domain::Telemetry::Altitude, 0));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(eph),
                             parameters.value(domain::Telemetry::Eph, 0));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(epv),
                             parameters.value(domain::Telemetry::Epv, 0));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(satellitesVisible),
                             parameters.value(domain::Telemetry::SatellitesVisible, 0));
}

void VehicleDisplayPresenter::updatePowerSystem(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(powerSystem), PROPERTY(throttle),
                             parameters.value(domain::Telemetry::Throttle, 0));
}

void VehicleDisplayPresenter::updateBattery(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(present),
                             parameters.value(domain::Telemetry::Present, 0));
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(enabled),
                             parameters.value(domain::Telemetry::Enabled, 0));
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(operational),
                             parameters.value(domain::Telemetry::Operational, 0));
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(voltage),
                             parameters.value(domain::Telemetry::Voltage, 0));
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(current),
                             parameters.value(domain::Telemetry::Current, 0));
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(percentage),
                             parameters.value(domain::Telemetry::Percentage, 0));
}

void VehicleDisplayPresenter::updatePitot(const domain::Telemetry::TelemetryMap& parameters)
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

void VehicleDisplayPresenter::updateBarometric(const domain::Telemetry::TelemetryMap& parameters)
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

void VehicleDisplayPresenter::updateRadalt(const domain::Telemetry::TelemetryMap& parameters)
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

void VehicleDisplayPresenter::updatePosition(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(position),
                             parameters.value(domain::Telemetry::Coordinate,
                                              QVariant::fromValue(QGeoCoordinate())));
}

void VehicleDisplayPresenter::updateHome(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(homePosition),
                             parameters.value(domain::Telemetry::Coordinate,
                                              QVariant::fromValue(QGeoCoordinate())));
}

void VehicleDisplayPresenter::updateFlightControl(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(flightControl), PROPERTY(desiredPitch),
                             parameters.value(domain::Telemetry::DesiredPitch, 0));
    this->setVehicleProperty(PROPERTY(flightControl), PROPERTY(desiredRoll),
                             parameters.value(domain::Telemetry::DesiredRoll, 0));
    this->setVehicleProperty(PROPERTY(flightControl), PROPERTY(desiredHeading),
                             parameters.value(domain::Telemetry::DesiredHeading, 0));
}

void VehicleDisplayPresenter::updateNavigator(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(navigator), PROPERTY(airspeedError),
                             parameters.value(domain::Telemetry::AirspeedError, false));
    this->setVehicleProperty(PROPERTY(navigator), PROPERTY(altitudeError),
                             parameters.value(domain::Telemetry::AltitudeError, false));
    this->setVehicleProperty(PROPERTY(navigator), PROPERTY(targetBearing),
                             parameters.value(domain::Telemetry::TargetBearing, 0));
    this->setVehicleProperty(PROPERTY(navigator), PROPERTY(targetDistance),
                             parameters.value(domain::Telemetry::Distance, 0));
    this->setVehicleProperty(PROPERTY(navigator), PROPERTY(trackError),
                             parameters.value(domain::Telemetry::TrackError, 0));
}

void VehicleDisplayPresenter::updateWind(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(wind), PROPERTY(direction),
                             parameters.value(domain::Telemetry::Yaw, false));
    this->setVehicleProperty(PROPERTY(wind), PROPERTY(speed),
                             parameters.value(domain::Telemetry::Speed, false));
}

void VehicleDisplayPresenter::connectView(QObject* view)
{
    BasePresenter::connectView(view);

    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(vibration),
                             QVariant::fromValue(m_vibrationModel));
}

