#include "vehicles_presenter.h"

// Qt
#include <QVariant>

// Internal
#include "vehicle_service.h"
#include "vehicle_description.h"

#include "description_vehicle_presenter.h"

using namespace presentation;

class VehiclesPresenter::Impl
{
public:
    domain::VehicleService* service;

    QList<DescriptionVehiclePresenter*> vehiclePresenters;
};

VehiclesPresenter::VehiclesPresenter(domain::VehicleService* service,
                                     QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->service = service;

    connect(service, &domain::VehicleService::vehicleAdded,
            this, &VehiclesPresenter::onVehicleAdded);
    connect(service, &domain::VehicleService::vehicleRemoved,
            this, &VehiclesPresenter::onVehicleRemoved);

    for (const data_source::VehicleDescriptionPtr& description:
         service->vehicles())
    {
        d->vehiclePresenters.append(new DescriptionVehiclePresenter(
                                        service, description, this));
    }
}

VehiclesPresenter::~VehiclesPresenter()
{}

void VehiclesPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(addVehicle()), this, SLOT(onAddVehicle()));

    this->updateVehicles();
}

void VehiclesPresenter::onVehicleAdded(
        const data_source::VehicleDescriptionPtr& vehicle)
{
    d->vehiclePresenters.append(new DescriptionVehiclePresenter(
                                    d->service, vehicle, this));
    this->updateVehicles();
}

void VehiclesPresenter::onVehicleRemoved(
        const data_source::VehicleDescriptionPtr& vehicle)
{
    for (DescriptionVehiclePresenter* vehiclePresenter: d->vehiclePresenters)
    {
        if (vehiclePresenter->description() != vehicle) continue;

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
    auto description = data_source::VehicleDescriptionPtr::create();

    description->setName(tr("New Vehicle"));

    d->service->saveVehicle(description);
}
