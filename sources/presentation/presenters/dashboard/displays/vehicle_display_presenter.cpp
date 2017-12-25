#include "vehicle_display_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

VehicleDisplayPresenter::VehicleDisplayPresenter(QObject* parent):
    ControlDisplayPresenter(parent)
{}

void VehicleDisplayPresenter::connectNode(domain::Telemetry* node)
{
    ControlDisplayPresenter::connectNode(node);

    this->chainNode(node->childNode(domain::Telemetry::Ahrs),
                    std::bind(&VehicleDisplayPresenter::updateAhrs, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Satellite),
                    std::bind(&VehicleDisplayPresenter::updateSatellite, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::PowerSystem),
                    std::bind(&VehicleDisplayPresenter::updatePowerSystem, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Barometric),
                    std::bind(&VehicleDisplayPresenter::updateBarometric, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::HomePosition),
                    std::bind(&VehicleDisplayPresenter::updateHomeAltitude, this, std::placeholders::_1));
}

void VehicleDisplayPresenter::updateAhrs(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(ahrsEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(ahrsOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(pitch), parameters.value(domain::Telemetry::Pitch, 0));
    this->setViewProperty(PROPERTY(roll), parameters.value(domain::Telemetry::Roll, 0));
    this->setViewProperty(PROPERTY(yaw), parameters.value(domain::Telemetry::Yaw, 0));
}

void VehicleDisplayPresenter::updateSatellite(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(satelliteEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(satelliteOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(groundspeed), parameters.value(domain::Telemetry::Groundspeed, 0));
    this->setViewProperty(PROPERTY(satelliteAltitude), parameters.value(domain::Telemetry::Altitude, 0));
}

void VehicleDisplayPresenter::updatePowerSystem(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(throttle), parameters.value(domain::Telemetry::Throttle, 0));
}

void VehicleDisplayPresenter::updateBarometric(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(barometricEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(barometricOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(barometricAltitude), parameters.value(domain::Telemetry::Altitude, 0));
    this->setViewProperty(PROPERTY(barometricClimb), parameters.value(domain::Telemetry::Climb, 0));
}

void VehicleDisplayPresenter::updateHomeAltitude(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(homeAltitude), parameters.value(domain::Telemetry::Altitude, 0));
}
