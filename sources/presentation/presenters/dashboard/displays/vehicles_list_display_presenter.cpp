#include "vehicles_list_display_presenter.h"

// Qt
#include <QSortFilterProxyModel>
#include <QVariant>
#include <QDebug>

// Internal
#include "vehicle.h"

#include "service_registry.h"
#include "vehicle_service.h"

#include "vehicles_model.h"
#include "vehicles_sorting_model.h"

using namespace presentation;

class VehiclesListDisplayPresenter::Impl
{
public:
     domain::VehicleService* service = serviceRegistry->vehicleService();

     VehiclesModel vehiclesModel;
     VehiclesSortingModel sortingModel;
};

VehiclesListDisplayPresenter::VehiclesListDisplayPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->vehiclesModel.setVehicles(d->service->vehicles());
    d->sortingModel.setSourceModel(&d->vehiclesModel);

    connect(d->service, &domain::VehicleService::vehicleAdded,
            this, [this](const dto::VehiclePtr& vehicle) {
        d->vehiclesModel.addVehicle(vehicle);
    });

    connect(d->service, &domain::VehicleService::vehicleChanged,
            this, [this](const dto::VehiclePtr& vehicle) {
        d->vehiclesModel.updateVehicle(vehicle);
    });

    connect(d->service, &domain::VehicleService::vehicleRemoved,
            this, [this](const dto::VehiclePtr& vehicle) {
        d->vehiclesModel.removeVehicle(vehicle);
    });
}

VehiclesListDisplayPresenter::~VehiclesListDisplayPresenter()
{}

void VehiclesListDisplayPresenter::connectView(QObject* view)
{
    BasePresenter::connectView(view);

    this->setViewProperty(PROPERTY(vehicles), QVariant::fromValue(&d->sortingModel));
}
