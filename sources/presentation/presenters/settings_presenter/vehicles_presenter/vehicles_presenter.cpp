#include "vehicles_presenter.h"

// Qt
#include <QVariant>

// Internal
#include "service_registry.h"
#include "vehicle_service.h"
#include "vehicle.h"

#include "description_vehicle_presenter.h"

using namespace presentation;

class VehiclesPresenter::Impl
{
public:
    domain::VehicleService* service;

    QList<DescriptionVehiclePresenter*> vehiclePresenters;
};

VehiclesPresenter::VehiclesPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->service = domain::ServiceRegistry::vehicleService();

    connect(d->service, &domain::VehicleService::vehicleAdded,
            this, &VehiclesPresenter::onVehicleAdded);
    connect(d->service, &domain::VehicleService::vehicleRemoved,
            this, &VehiclesPresenter::onVehicleRemoved);

    for (const dao::VehiclePtr& vehicle: d->service->vehicles())
    {
        d->vehiclePresenters.append(new DescriptionVehiclePresenter(d->service, vehicle, this));
    }
}

VehiclesPresenter::~VehiclesPresenter()
{}

void VehiclesPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(addVehicle()), this, SLOT(onAddVehicle()));

    this->updateVehicles();
}

void VehiclesPresenter::onVehicleAdded(const dao::VehiclePtr& vehicle)
{
    d->vehiclePresenters.append(new DescriptionVehiclePresenter(d->service, vehicle, this));
    this->updateVehicles();
}

void VehiclesPresenter::onVehicleRemoved(const dao::VehiclePtr& vehicle)
{
    for (DescriptionVehiclePresenter* vehiclePresenter: d->vehiclePresenters)
    {
        if (vehiclePresenter->vehicle() != vehicle) continue;

        d->vehiclePresenters.removeOne(vehiclePresenter);
        delete vehiclePresenter;
        this->updateVehicles();
        return;
    }
}

void VehiclesPresenter::updateVehicles()
{
    QList<QObject*> objectList;
    for (DescriptionVehiclePresenter* vehiclePresenter: d->vehiclePresenters)
    {
        objectList.append(vehiclePresenter);
    }

    this->setViewProperty(PROPERTY(vehicles), QVariant::fromValue(objectList));
}

void VehiclesPresenter::onAddVehicle()
{
    auto description = dao::VehiclePtr::create();

    description->setName(tr("New Vehicle"));

    d->service->save(description);
}
