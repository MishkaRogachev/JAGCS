#include "vehicle_presenter.h"

// Qt
#include <QVariant>

// Internal
#include "vehicle.h"

#include "telemetry_service.h"
#include "availables.h"
#include "status.h"
#include "attitude.h"
#include "sns.h"

#include "attitude.h"

using namespace presentation;

VehiclePresenter::VehiclePresenter(domain::TelemetryService* telemetryService,
                                   const db::VehiclePtr& vehicle, QObject* parent):
    BasePresenter(parent),
    m_telemetryService(telemetryService),
    m_vehicle(vehicle)
{}

void VehiclePresenter::updateVehicle()
{
    this->setViewProperty("name", m_vehicle->name());
    this->setViewProperty("mavId", m_vehicle->mavId());
}

void VehiclePresenter::updateOnline(bool online)
{
    this->setViewProperty("online", online);
}

void VehiclePresenter::updateStatus(const domain::Status& status)
{
    this->setViewProperty("armed", status.armed());
    this->setViewProperty("modeString", status.modeString());
}

void VehiclePresenter::updateAvailables(const domain::Availables& availables)
{
    this->setViewProperty("ahrsAvailable", availables.ahrsAvailable());
    this->setViewProperty("airSpeedAvailable", availables.airSpeedAvailable());
    this->setViewProperty("barometerAvailable", availables.barometerAvailable());
    this->setViewProperty("compassAvailable", availables.compassAvailable());
}

void VehiclePresenter::updateAttitude(const domain::Attitude& attitude)
{
    this->setViewProperty("pitch", attitude.pitch());
    this->setViewProperty("roll", attitude.roll());
}

void VehiclePresenter::updateSns(const domain::Sns& sns)
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
    if (!view) return;
    this->updateVehicle();

    this->updateOnline(m_telemetryService->isOnline(m_vehicle->id()));
    this->updateStatus(m_telemetryService->status(m_vehicle->id()));
    this->updateAvailables(m_telemetryService->availables(m_vehicle->id()));
    this->updateAttitude(m_telemetryService->attitude(m_vehicle->id()));
    this->updateSns(m_telemetryService->sns(m_vehicle->id()));
}
