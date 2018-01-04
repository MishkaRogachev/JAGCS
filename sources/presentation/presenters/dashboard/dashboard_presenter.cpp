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
}

DashboardPresenter::~DashboardPresenter()
{}

void DashboardPresenter::connectView(QObject* view)
{
    view->setProperty(PROPERTY(displays), QVariant::fromValue(&d->displaysModel));
}
