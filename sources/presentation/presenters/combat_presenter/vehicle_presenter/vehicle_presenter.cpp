#include "vehicle_presenter.h"

// Qt
#include <QVariant>

// Internal
#include "vehicle_description.h"
#include "telemetry_service.h"

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

void VehiclePresenter::setAttitude(const domain::Attitude& attitude)
{
    this->setViewProperty("pitch", attitude.pitch());
    this->setViewProperty("roll", attitude.roll());
    this->setViewProperty("yaw", attitude.yaw());
}

void VehiclePresenter::connectView(QObject* view)
{
    this->updateVehicle();
}
