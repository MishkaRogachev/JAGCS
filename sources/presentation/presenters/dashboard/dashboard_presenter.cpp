#include "dashboard_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "vehicle.h"

#include "service_registry.h"
#include "vehicle_service.h"

#include "vehicle_display_model.h"

using namespace presentation;

class DashboardPresenter::Impl
{
public:
    domain::VehicleService* service = domain::ServiceRegistry::vehicleService();
    dao::VehiclePtr vehicle;

    QAbstractItemModel* model = nullptr;
};

DashboardPresenter::DashboardPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    connect(d->service, &domain::VehicleService::vehicleChanged,
            [this](const dao::VehiclePtr& vehicle) {
        if (vehicle == d->vehicle) this->updateSelection();
    });
}

DashboardPresenter::~DashboardPresenter()
{}

void DashboardPresenter::setVehicle(int id)
{
    d->vehicle = d->service->vehicle(id);
    this->updateSelection();
}

void DashboardPresenter::updateSelection()
{
    if (d->model)
    {
        delete d->model;
        d->model = nullptr;
        this->setViewProperty(PROPERTY(instruments), QVariant::fromValue(nullptr));
    }

    if (d->vehicle)
    {
        d->model = new VehicleDisplayModel(d->vehicle, this);
    }

    this->setViewProperty(PROPERTY(instruments), QVariant::fromValue(d->model));
}
