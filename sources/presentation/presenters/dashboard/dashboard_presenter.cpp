#include "dashboard_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "vehicle.h"

#include "service_registry.h"
#include "vehicle_service.h"

#include "vehicle_dashboard_factory.h"

using namespace presentation;

class DashboardPresenter::Impl
{
public:
    domain::VehicleService* service = domain::ServiceRegistry::vehicleService();
    dao::VehiclePtr vehicle;
};

DashboardPresenter::DashboardPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    connect(d->service, &domain::VehicleService::vehicleChanged,
            [this](const dao::VehiclePtr& vehicle) {
        if (vehicle == d->vehicle) this->updateVehicle();
    });
}

DashboardPresenter::~DashboardPresenter()
{}

void DashboardPresenter::setVehicle(int id)
{
    d->vehicle = d->service->vehicle(id);

    this->setViewProperty(PROPERTY(instruments), QVariantList()); // TMP
    this->updateVehicle();
}

void DashboardPresenter::updateVehicle()
{
    if (d->vehicle)
    {
        this->setViewProperty(PROPERTY(online), d->vehicle->isOnline());

        // TODO: handle VehicleInstruments dao
        VehicleDashboardFactory f(d->vehicle);
        this->setViewProperty(PROPERTY(instruments), f.create());
    }
    else
    {
        this->setViewProperty(PROPERTY(instruments), QVariantList());
    }
}
