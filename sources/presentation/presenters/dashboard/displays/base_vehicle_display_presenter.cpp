#include "base_vehicle_display_presenter.h"

// Qt
#include <QTime>
#include <QVector3D>
#include <QGeoCoordinate>
#include <QDebug>

// Internal
#include "vibration_model.h"

using namespace presentation;

BaseVehicleDisplayPresenter::BaseVehicleDisplayPresenter(QObject* parent):
    CommonVehicleDisplayPresenter(parent),
    m_vibrationModel(new VibrationModel(this))
{}

void BaseVehicleDisplayPresenter::connectView(QObject* view)
{
    CommonVehicleDisplayPresenter::connectView(view);

    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(vibration),
                             QVariant::fromValue(m_vibrationModel));
}


void BaseVehicleDisplayPresenter::connectNode(domain::Telemetry* node)
{
    CommonVehicleDisplayPresenter::connectNode(node);

    domain::Telemetry* ahrs = node->childNode(domain::Telemetry::Ahrs);
    this->chainNode(ahrs, std::bind(&BaseVehicleDisplayPresenter::updateAhrs,
                                    this, std::placeholders::_1));
    this->chainNode(ahrs->childNode(domain::Telemetry::Compass),
                    std::bind(&BaseVehicleDisplayPresenter::updateCompass,
                              this, std::placeholders::_1));

    this->chainNode(node->childNode(domain::Telemetry::Satellite),
                    std::bind(&BaseVehicleDisplayPresenter::updateSatellite,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::PowerSystem),
                    std::bind(&BaseVehicleDisplayPresenter::updatePowerSystem,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Battery),
                    std::bind(&BaseVehicleDisplayPresenter::updateBattery,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::HomePosition),
                    std::bind(&BaseVehicleDisplayPresenter::updateHome,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Position),
                    std::bind(&BaseVehicleDisplayPresenter::updatePosition,
                              this, std::placeholders::_1));
}

void BaseVehicleDisplayPresenter::updateAhrs(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(present),
                             parameters.value(domain::Telemetry::Present, true));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(enabled),
                             parameters.value(domain::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(operational),
                             parameters.value(domain::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(pitch),
                             parameters.value(domain::Telemetry::Pitch, qQNaN()));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(roll),
                             parameters.value(domain::Telemetry::Roll, qQNaN()));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(yaw),
                             parameters.value(domain::Telemetry::Yaw, qQNaN()));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(yawspeed),
                             parameters.value(domain::Telemetry::YawSpeed, qQNaN()));

    // TODO: telemetry timestamp
    Vibration vibration;
    vibration.timestamp = QTime::currentTime().msecsSinceStartOfDay();
    vibration.data = parameters.value(domain::Telemetry::Vibration).value<QVector3D>();

    m_vibrationModel->addData(vibration);
}

void BaseVehicleDisplayPresenter::updateCompass(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(compass), PROPERTY(present),
                             parameters.value(domain::Telemetry::Present, true));
    this->setVehicleProperty(PROPERTY(compass), PROPERTY(enabled),
                             parameters.value(domain::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(compass), PROPERTY(operational),
                             parameters.value(domain::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(compass), PROPERTY(heading),
                             parameters.value(domain::Telemetry::Heading, qQNaN()));
}

void BaseVehicleDisplayPresenter::updateSatellite(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(present),
                             parameters.value(domain::Telemetry::Present, true));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(enabled),
                             parameters.value(domain::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(operational),
                             parameters.value(domain::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(fix),
                             parameters.value(domain::Telemetry::Fix, -1));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(course),
                             parameters.value(domain::Telemetry::Course, qQNaN()));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(groundspeed),
                             parameters.value(domain::Telemetry::Groundspeed, qQNaN()));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(coordinate),
                             parameters.value(domain::Telemetry::Coordinate,
                                              QVariant::fromValue(QGeoCoordinate())));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(altitude),
                             parameters.value(domain::Telemetry::Altitude, qQNaN()));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(eph),
                             parameters.value(domain::Telemetry::Eph, 0));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(epv),
                             parameters.value(domain::Telemetry::Epv, 0));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(satellitesVisible),
                             parameters.value(domain::Telemetry::SatellitesVisible, 0));
}

void BaseVehicleDisplayPresenter::updatePowerSystem(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(powerSystem), PROPERTY(throttle),
                             parameters.value(domain::Telemetry::Throttle, 0));
}

void BaseVehicleDisplayPresenter::updateBattery(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(present),
                             parameters.value(domain::Telemetry::Present, true));
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(enabled),
                             parameters.value(domain::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(operational),
                             parameters.value(domain::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(voltage),
                             parameters.value(domain::Telemetry::Voltage, qQNaN()));
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(current),
                             parameters.value(domain::Telemetry::Current, qQNaN()));
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(percentage),
                             parameters.value(domain::Telemetry::Percentage, 0));
}

void BaseVehicleDisplayPresenter::updatePosition(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(position),
                             parameters.value(domain::Telemetry::Coordinate,
                                              QVariant::fromValue(QGeoCoordinate())));
}

void BaseVehicleDisplayPresenter::updateHome(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(home), PROPERTY(position),
                             parameters.value(domain::Telemetry::Coordinate,
                                              QVariant::fromValue(QGeoCoordinate())));

    this->setVehicleProperty(PROPERTY(home), PROPERTY(altitude),
                             parameters.value(domain::Telemetry::Altitude, qQNaN()));
}

