#include "vehicle_presenter.h"

// Qt
#include <QVariant>

// Internal
#include "vehicle_description.h"

#include "availables.h"
#include "status.h"
#include "attitude.h"
#include "sns.h"

#include "attitude.h"

using namespace presentation;

VehiclePresenter::VehiclePresenter(
        const db::VehicleDescriptionPtr& vehicle,
        QObject* parent):
    BasePresenter(parent),
    m_vehicle(vehicle)
{}

void VehiclePresenter::updateVehicle()
{
    this->setViewProperty("name", m_vehicle ? m_vehicle->name() : tr("None"));
    this->setViewProperty("mavId", m_vehicle ? m_vehicle->mavId() : -1);
}

void VehiclePresenter::setOnline(bool online)
{
    this->setViewProperty("online", online);
}

void VehiclePresenter::setStatus(const domain::Status& status)
{
    this->setViewProperty("armed", status.armed());
    this->setViewProperty("modeString", status.modeString());
}

void VehiclePresenter::setAvailables(const domain::Availables& availables)
{
    this->setViewProperty("ahrsAvailable", availables.ahrsAvailable());
    this->setViewProperty("airSpeedAvailable", availables.airSpeedAvailable());
    this->setViewProperty("barometerAvailable", availables.barometerAvailable());
    this->setViewProperty("compassAvailable", availables.compassAvailable());
}

void VehiclePresenter::setAttitude(const domain::Attitude& attitude)
{
    this->setViewProperty("pitch", attitude.pitch());
    this->setViewProperty("roll", attitude.roll());
    this->setViewProperty("yaw", attitude.yaw());
}

void VehiclePresenter::setSns(const domain::Sns& sns)
{
    this->setViewProperty("coordinate", QVariant::fromValue(sns.coordinate()));
    this->setViewProperty("snsAltitude", QVariant::fromValue(sns.altitude()));
    this->setViewProperty("snsCourse", QVariant::fromValue(sns.course()));
    this->setViewProperty("groundSpeed", QVariant::fromValue(sns.groundSpeed()));
    this->setViewProperty("snsFix", QVariant::fromValue(sns.fix()));
    this->setViewProperty("eph", QVariant::fromValue(sns.eph()));
    this->setViewProperty("epv", QVariant::fromValue(sns.epv()));
}

void VehiclePresenter::connectView(QObject* view)
{
    this->updateVehicle();
}
