#include "planning_presenter.h"

// Internal
#include "vehicle.h"

#include "service_registry.h"
#include "vehicle_service.h"

// Qt
#include <QVariant>
#include <QDebug>

using namespace presentation;

class PlanningPresenter::Impl
{
public:
    domain::VehicleService* const service = domain::ServiceRegistry::vehicleService();
};

PlanningPresenter::PlanningPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    connect(d->service, &domain::VehicleService::vehicleAdded,
            this, &PlanningPresenter::updateVehicles);
    connect(d->service, &domain::VehicleService::vehicleRemoved,
            this, &PlanningPresenter::updateVehicles);
    connect(d->service, &domain::VehicleService::vehicleChanged,
            this, &PlanningPresenter::updateVehicles);
}

PlanningPresenter::~PlanningPresenter()
{}

void PlanningPresenter::updateVehicles()
{
    QVariantList vehicles;
    vehicles.append(QVariant::fromValue(dao::Vehicle()));

    for (const dao::VehiclePtr& vehicle: d->service->vehicles())
    {
        vehicles.append(QVariant::fromValue(*vehicle));
    }

    this->setViewProperty(PROPERTY(vehicles), vehicles);
}
