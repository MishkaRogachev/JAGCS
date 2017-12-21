#include "base_display_presenter.h"

// Qt
#include <QDebug>

//Internal
#include "vehicle.h"

#include "service_registry.h"
#include "telemetry_service.h"
#include "vehicle_service.h"

using namespace presentation;

BaseDisplayPresenter::BaseDisplayPresenter(QObject* parent):
    BasePresenter(parent)
{
    connect(domain::ServiceRegistry::vehicleService(),
            &domain::VehicleService::vehicleChanged, this,
            [this](const dao::VehiclePtr& vehicle)
    {
        if (vehicle->id() != m_vehicleId) return;

        this->setViewProperty(PROPERTY(online), vehicle->isOnline());
    });
}

int BaseDisplayPresenter::vehicleId() const
{
    return m_vehicleId;
}

void BaseDisplayPresenter::setVehicle(int vehicleId)
{
    m_vehicleId = vehicleId;

    dao::VehiclePtr vehicle = domain::ServiceRegistry::vehicleService()->vehicle(vehicleId);
    if (vehicle.isNull()) return;

    this->setViewProperty(PROPERTY(vehicleName), vehicle->name());
    this->setViewProperty(PROPERTY(online), vehicle->isOnline());
}
