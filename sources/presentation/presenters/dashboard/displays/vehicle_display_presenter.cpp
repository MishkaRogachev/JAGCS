#include "vehicle_display_presenter.h"

// Qt
#include <QVector3D>
#include <QTime>
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

    this->chainNode(node->childNode(domain::Telemetry::System),
                    std::bind(&VehicleDisplayPresenter::updateSystem, this, std::placeholders::_1));

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
    this->chainNode(node->childNode(domain::Telemetry::Rangefinder),
                    std::bind(&VehicleDisplayPresenter::updateRangefinder, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Position),
                    std::bind(&VehicleDisplayPresenter::updatePosition, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Navigator),
                    std::bind(&VehicleDisplayPresenter::updateNavigator, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::FlightControl),
                    std::bind(&VehicleDisplayPresenter::updateFlightControl, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Wind),
                    std::bind(&VehicleDisplayPresenter::updateWind, this, std::placeholders::_1));
}

void VehicleDisplayPresenter::updateSystem(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(armed), parameters.value(domain::Telemetry::Armed));
    this->setViewProperty(PROPERTY(guided), parameters.value(domain::Telemetry::Guided));
    this->setViewProperty(PROPERTY(vehicleState), parameters.value(domain::Telemetry::State));
}

void VehicleDisplayPresenter::updateAhrs(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(ahrsEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(ahrsOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(pitch), parameters.value(domain::Telemetry::Pitch, 0));
    this->setViewProperty(PROPERTY(roll), parameters.value(domain::Telemetry::Roll, 0));
    this->setViewProperty(PROPERTY(yaw), parameters.value(domain::Telemetry::Yaw, 0));
    this->setViewProperty(PROPERTY(yawspeed), parameters.value(domain::Telemetry::YawSpeed, 0));

    // TODO: telemetry timestamp
    Vibration vibration;
    vibration.timestamp = QTime::currentTime().msecsSinceStartOfDay();
    vibration.data = parameters.value(domain::Telemetry::Vibration).value<QVector3D>();

    m_vibrationModel->addData(vibration);
}

void VehicleDisplayPresenter::updateCompass(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(compassEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(compassOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(heading), parameters.value(domain::Telemetry::Heading, 0));
}

void VehicleDisplayPresenter::updateEkf(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(velocityVariance),
                          parameters.value(domain::Telemetry::VelocityVariance, 0.0));
    this->setViewProperty(PROPERTY(verticalVariance),
                          parameters.value(domain::Telemetry::VerticalVariance, 0.0));
    this->setViewProperty(PROPERTY(horizontVariance),
                          parameters.value(domain::Telemetry::HorizontVariance, 0.0));
    this->setViewProperty(PROPERTY(compassVariance),
                          parameters.value(domain::Telemetry::CompassVariance, 0.0));
    this->setViewProperty(PROPERTY(terrainAltitudeVariance),
                          parameters.value(domain::Telemetry::TerrainAltitudeVariance, 0.0));
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

void VehicleDisplayPresenter::updateBattery(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(batteryEnabled), parameters.value(domain::Telemetry::Enabled, 0));
    this->setViewProperty(PROPERTY(batteryOperational), parameters.value(domain::Telemetry::Operational, 0));
    this->setViewProperty(PROPERTY(batteryVoltage), parameters.value(domain::Telemetry::Voltage, 0));
    this->setViewProperty(PROPERTY(batteryCurrent), parameters.value(domain::Telemetry::Current, 0));
    this->setViewProperty(PROPERTY(batteryPercentage), parameters.value(domain::Telemetry::Percentage, 0));
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
    this->setViewProperty(PROPERTY(airspeedError), parameters.value(domain::Telemetry::AirspeedError, false));
    this->setViewProperty(PROPERTY(altitudeError), parameters.value(domain::Telemetry::AltitudeError, false));
    this->setViewProperty(PROPERTY(targetBearing), parameters.value(domain::Telemetry::TargetBearing, 0));
    this->setViewProperty(PROPERTY(targetDistance), parameters.value(domain::Telemetry::Distance, 0));
    this->setViewProperty(PROPERTY(trackError), parameters.value(domain::Telemetry::TrackError, 0));
}

void VehicleDisplayPresenter::updateFlightControl(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(desiredPitch), parameters.value(domain::Telemetry::DesiredPitch, 0));
    this->setViewProperty(PROPERTY(desiredRoll), parameters.value(domain::Telemetry::DesiredRoll, 0));
    this->setViewProperty(PROPERTY(desiredHeading), parameters.value(domain::Telemetry::DesiredHeading, 0));
}

void VehicleDisplayPresenter::updateWind(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(windDirection), parameters.value(domain::Telemetry::Yaw, false));
    this->setViewProperty(PROPERTY(windSpeed), parameters.value(domain::Telemetry::Speed, false));
}

void VehicleDisplayPresenter::connectView(QObject* view)
{
    view->setProperty(PROPERTY(vibration), QVariant::fromValue(m_vibrationModel));

    BasePresenter::connectView(view);
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
