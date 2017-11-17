#include "planning_presenter.h"

// Internal
#include "vehicle.h"

#include "service_registry.h"
#include "vehicle_service.h"

#include "mission_list_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

using namespace presentation;

class PlanningPresenter::Impl
{
public:
    domain::VehicleService* const service = domain::ServiceRegistry::vehicleService();
    MissionListPresenter* missions;
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

    d->missions = new MissionListPresenter(this);
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

void PlanningPresenter::connectView(QObject* view)
{
    d->missions->setView(this->view()->findChild<QObject*>("missions"));

    this->updateVehicles();
}
