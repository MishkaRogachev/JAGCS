#include "dashboard_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "vehicle.h"

#include "service_registry.h"
#include "vehicle_service.h"

#include "displays_model.h"

using namespace presentation;

class DashboardPresenter::Impl
{
public:
    dao::VehiclePtr selectedVehicle;
    domain::VehicleService* service = domain::ServiceRegistry::vehicleService();

    DisplaysModel displaysModel;
};

DashboardPresenter::DashboardPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
     for (const dao::VehiclePtr& vehicle: d->service->vehicles())
     {
         d->displaysModel.addVehicle(vehicle);
     }

     connect(d->service, &domain::VehicleService::vehicleAdded,
             &d->displaysModel, &DisplaysModel::addVehicle);
     connect(d->service, &domain::VehicleService::vehicleRemoved,
             &d->displaysModel, &DisplaysModel::removeVehicle);
     connect(d->service, &domain::VehicleService::vehicleChanged,
             this, [this](const dao::VehiclePtr& vehicle){
                 if (d->selectedVehicle != vehicle) return;

                 this->view()->setProperty(PROPERTY(selectedVehicle), QVariant::fromValue(*vehicle));
             });
}

DashboardPresenter::~DashboardPresenter()
{}

void DashboardPresenter::selectVehicle(int vehicleId)
{
    dao::VehiclePtr vehicle = d->service->vehicle(vehicleId);

    if (vehicle == d->selectedVehicle) return;

    d->selectedVehicle = vehicle;
    if (vehicle)
    {
        this->view()->setProperty(PROPERTY(selectedVehicle), QVariant::fromValue(*vehicle));
    }
    else
    {
        this->view()->setProperty(PROPERTY(selectedVehicle), QVariant());
    }

    d->displaysModel.setSelectedVehicle(vehicle);
}

void DashboardPresenter::connectView(QObject* view)
{
    view->setProperty(PROPERTY(displays), QVariant::fromValue(&d->displaysModel));
}
