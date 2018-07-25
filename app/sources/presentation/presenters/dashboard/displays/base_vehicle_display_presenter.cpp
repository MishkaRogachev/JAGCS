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

void BaseVehicleDisplayPresenter::connectNode(data_source::Telemetry* node)
{
    this->chainNode(node->childNode(data_source::Telemetry::System),
                    std::bind(&BaseVehicleDisplayPresenter::updateSystem,
                              this, std::placeholders::_1));

    data_source::Telemetry* ahrs = node->childNode(data_source::Telemetry::Ahrs);
    this->chainNode(ahrs, std::bind(&BaseVehicleDisplayPresenter::updateAhrs,
                                    this, std::placeholders::_1));
    this->chainNode(ahrs->childNode(data_source::Telemetry::Compass),
                    std::bind(&BaseVehicleDisplayPresenter::updateCompass,
                              this, std::placeholders::_1));

    this->chainNode(node->childNode(data_source::Telemetry::Satellite),
                    std::bind(&BaseVehicleDisplayPresenter::updateSatellite,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(data_source::Telemetry::PowerSystem),
                    std::bind(&BaseVehicleDisplayPresenter::updatePowerSystem,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(data_source::Telemetry::Battery),
                    std::bind(&BaseVehicleDisplayPresenter::updateBattery,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(data_source::Telemetry::HomePosition),
                    std::bind(&BaseVehicleDisplayPresenter::updateHome,
                              this, std::placeholders::_1));
    this->chainNode(node->childNode(data_source::Telemetry::Position),
                    std::bind(&BaseVehicleDisplayPresenter::updatePosition,
                              this, std::placeholders::_1));
}

void BaseVehicleDisplayPresenter::updateSystem(const data_source::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(armed), parameters.value(data_source::Telemetry::Armed));
    this->setVehicleProperty(PROPERTY(guided), parameters.value(data_source::Telemetry::Guided));
    this->setVehicleProperty(PROPERTY(stab), parameters.value(data_source::Telemetry::Stabilized));
    this->setVehicleProperty(PROPERTY(vehicleState), parameters.value(data_source::Telemetry::State));
    this->setVehicleProperty(PROPERTY(mode), parameters.value(data_source::Telemetry::Mode));

    QVariantList modes;
    for (auto item: parameters.value(data_source::Telemetry::AvailableModes).value<
         QList<data_source::Telemetry::VehicleMode> >())
    {
        modes.append(QVariant::fromValue(item));
    }
    this->setVehicleProperty(PROPERTY(availableModes), modes);
}

void BaseVehicleDisplayPresenter::updateAhrs(const data_source::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(present),
                             parameters.value(data_source::Telemetry::Present, true));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(enabled),
                             parameters.value(data_source::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(operational),
                             parameters.value(data_source::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(pitch),
                             parameters.value(data_source::Telemetry::Pitch, qQNaN()));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(roll),
                             parameters.value(data_source::Telemetry::Roll, qQNaN()));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(yaw),
                             parameters.value(data_source::Telemetry::Yaw, qQNaN()));
    this->setVehicleProperty(PROPERTY(ahrs), PROPERTY(yawspeed),
                             parameters.value(data_source::Telemetry::YawSpeed, qQNaN()));

    // TODO: telemetry timestamp
    Vibration vibration;
    vibration.timestamp = QTime::currentTime().msecsSinceStartOfDay();
    vibration.data = parameters.value(data_source::Telemetry::Vibration).value<QVector3D>();

    m_vibrationModel->addData(vibration);
}

void BaseVehicleDisplayPresenter::updateCompass(const data_source::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(compass), PROPERTY(present),
                             parameters.value(data_source::Telemetry::Present, true));
    this->setVehicleProperty(PROPERTY(compass), PROPERTY(enabled),
                             parameters.value(data_source::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(compass), PROPERTY(operational),
                             parameters.value(data_source::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(compass), PROPERTY(heading),
                             parameters.value(data_source::Telemetry::Heading, qQNaN()));
}

void BaseVehicleDisplayPresenter::updateSatellite(const data_source::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(present),
                             parameters.value(data_source::Telemetry::Present, true));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(enabled),
                             parameters.value(data_source::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(operational),
                             parameters.value(data_source::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(fix),
                             parameters.value(data_source::Telemetry::Fix, -1));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(course),
                             parameters.value(data_source::Telemetry::Course, qQNaN()));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(groundspeed),
                             parameters.value(data_source::Telemetry::Groundspeed, qQNaN()));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(coordinate),
                             parameters.value(data_source::Telemetry::Coordinate,
                                              QVariant::fromValue(QGeoCoordinate())));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(altitude),
                             parameters.value(data_source::Telemetry::Altitude, qQNaN()));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(eph),
                             parameters.value(data_source::Telemetry::Eph, 0));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(epv),
                             parameters.value(data_source::Telemetry::Epv, 0));
    this->setVehicleProperty(PROPERTY(satellite), PROPERTY(satellitesVisible),
                             parameters.value(data_source::Telemetry::SatellitesVisible, 0));
}

void BaseVehicleDisplayPresenter::updatePowerSystem(const data_source::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(powerSystem), PROPERTY(throttle),
                             parameters.value(data_source::Telemetry::Throttle, 0));
}

void BaseVehicleDisplayPresenter::updateBattery(const data_source::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(present),
                             parameters.value(data_source::Telemetry::Present, true));
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(enabled),
                             parameters.value(data_source::Telemetry::Enabled, false));
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(operational),
                             parameters.value(data_source::Telemetry::Operational, false));
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(voltage),
                             parameters.value(data_source::Telemetry::Voltage, qQNaN()));
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(current),
                             parameters.value(data_source::Telemetry::Current, qQNaN()));
    this->setVehicleProperty(PROPERTY(battery), PROPERTY(percentage),
                             parameters.value(data_source::Telemetry::Percentage, 0));
}

void BaseVehicleDisplayPresenter::updatePosition(const data_source::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(position),
                             parameters.value(data_source::Telemetry::Coordinate,
                                              QVariant::fromValue(QGeoCoordinate())));
}

void BaseVehicleDisplayPresenter::updateHome(const data_source::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(home), PROPERTY(position),
                             parameters.value(data_source::Telemetry::Coordinate,
                                              QVariant::fromValue(QGeoCoordinate())));

    this->setVehicleProperty(PROPERTY(home), PROPERTY(altitude),
                             parameters.value(data_source::Telemetry::Altitude, qQNaN()));
}

