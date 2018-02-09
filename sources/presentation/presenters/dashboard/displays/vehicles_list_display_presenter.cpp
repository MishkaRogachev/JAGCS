#include "vehicles_list_display_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "vehicle.h"

#include "service_registry.h"
#include "vehicle_service.h"

#include "vehicles_model.h"

using namespace presentation;

class VehiclesListDisplayPresenter::Impl
{
public:
     domain::VehicleService* service = domain::ServiceRegistry::vehicleService();

     VehiclesModel vehicles;
};

VehiclesListDisplayPresenter::VehiclesListDisplayPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->vehicles.setVehicles(d->service->vehicles());

    connect(d->service, &domain::VehicleService::vehicleAdded,
            this, [this](const dao::VehiclePtr& vehicle) {
        d->vehicles.addVehicle(vehicle);
    });

    connect(d->service, &domain::VehicleService::vehicleRemoved,
            this, [this](const dao::VehiclePtr& vehicle) {
        d->vehicles.removeVehicle(vehicle);
    });
}

VehiclesListDisplayPresenter::~VehiclesListDisplayPresenter()
{}

void VehiclesListDisplayPresenter::connectView(QObject* view)
{
    BasePresenter::connectView(view);

    this->setViewProperty(PROPERTY(vehicles), QVariant::fromValue(&d->vehicles));
}
