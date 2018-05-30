#include "vehicles_list_display_presenter.h"

// Qt
#include <QSortFilterProxyModel>
#include <QVariant>
#include <QDebug>

// Internal
#include "vehicle.h"

#include "service_registry.h"
#include "vehicle_service.h"

#include "vehicle_list_model.h"
#include "vehicle_list_sorting_model.h"

using namespace presentation;

class VehiclesListDisplayPresenter::Impl
{
public:
     domain::VehicleService* service = serviceRegistry->vehicleService();

     VehicleListModel vehiclesModel;
     VehicleListSortingModel sortingModel;
};

VehiclesListDisplayPresenter::VehiclesListDisplayPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->vehiclesModel.setVehicles(d->service->vehicles());
    d->sortingModel.setSourceModel(&d->vehiclesModel);

    connect(d->service, &domain::VehicleService::vehicleAdded,
            &d->vehiclesModel, &VehicleListModel::addVehicle);
    connect(d->service, &domain::VehicleService::vehicleRemoved,
            &d->vehiclesModel, &VehicleListModel::removeVehicle);
    connect(d->service, &domain::VehicleService::vehicleChanged,
            &d->vehiclesModel, &VehicleListModel::updateVehicle);
}

VehiclesListDisplayPresenter::~VehiclesListDisplayPresenter()
{}

void VehiclesListDisplayPresenter::connectView(QObject* view)
{
    BasePresenter::connectView(view);

    this->setViewProperty(PROPERTY(vehicles), QVariant::fromValue(&d->sortingModel));
}
