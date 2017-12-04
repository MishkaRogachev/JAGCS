#include "topbar_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle.h"

#include "service_registry.h"
#include "vehicle_service.h"

using namespace presentation;

class TopbarPresenter::Impl
{
public:
    domain::VehicleService* vehicleService = domain::ServiceRegistry::vehicleService();

};

TopbarPresenter::TopbarPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    connect(d->vehicleService, &domain::VehicleService::vehicleAdded,
            this, &TopbarPresenter::updateVehicles);
    connect(d->vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &TopbarPresenter::updateVehicles);
    connect(d->vehicleService, &domain::VehicleService::vehicleChanged,
            this, &TopbarPresenter::updateVehicles);
}

TopbarPresenter::~TopbarPresenter()
{}

void TopbarPresenter::updateVehicles()
{
    QVariantList vehicles;
    vehicles.append(QVariant::fromValue(dao::Vehicle()));

    for (const dao::VehiclePtr& vehicle: d->vehicleService->vehicles())
    {
        vehicles.append(QVariant::fromValue(*vehicle));
    }

    this->setViewProperty(PROPERTY(vehicles), vehicles);
}

void TopbarPresenter::connectView(QObject* view)
{

}


