#include "planning_presenter.h"

// Internal
#include "vehicle.h"

#include "service_registry.h"
#include "vehicle_service.h"

// Qt
#include <QVariant>
#include <QDebug>

using namespace presentation;

PlanningPresenter::PlanningPresenter(QObject* parent):
    BasePresenter(parent),
    m_service(domain::ServiceRegistry::vehicleService())
{
    connect(m_service, &domain::VehicleService::vehicleAdded,
            this, &PlanningPresenter::updateVehicles);
    connect(m_service, &domain::VehicleService::vehicleRemoved,
            this, &PlanningPresenter::updateVehicles);
    connect(m_service, &domain::VehicleService::vehicleChanged,
            this, &PlanningPresenter::updateVehicles);
}

void PlanningPresenter::updateVehicles()
{
    QVariantList vehicles;
    vehicles.append(QVariant::fromValue(dao::Vehicle()));

    for (const dao::VehiclePtr& vehicle: m_service->vehicles())
    {
        vehicles.append(QVariant::fromValue(*vehicle));
    }

    this->setViewProperty(PROPERTY(vehicles), vehicles);
}
