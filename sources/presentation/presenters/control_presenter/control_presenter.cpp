#include "control_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "domain_entry.h"

#include "db_facade.h"
#include "vehicle.h"

#include "telemetry_service.h"

#include "location_map_presenter.h"
#include "vehicle_dashboard_factory.h"
#include "dashboard_presenter.h"

using namespace presentation;

class ControlPresenter::Impl
{
public:
    db::DbFacade* dbFacade;
    domain::TelemetryService* telemetryService;

    AbstractMapPresenter* map;
    QMap<int, DashboardPresenter*> vehicleDashboards;
};

ControlPresenter::ControlPresenter(domain::DomainEntry* entry, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->dbFacade = entry->dbFacade();
    d->telemetryService = entry->telemetryService();

    d->map = new LocationMapPresenter(entry, this);

    connect(d->dbFacade, &db::DbFacade::vehicleAdded, this, &ControlPresenter::onVehicleAdded);
    connect(d->dbFacade, &db::DbFacade::vehicleRemoved, this, &ControlPresenter::onVehicleRemoved);
    connect(d->dbFacade, &db::DbFacade::vehicleChanged, this, &ControlPresenter::onVehicleChanged);

    for (const db::VehiclePtr& vehicle: d->dbFacade->vehicles())
    {
       this->onVehicleAdded(vehicle);
    }
}

ControlPresenter::~ControlPresenter()
{}

void ControlPresenter::updateVehicles()
{
    QList<QObject*> objectList;
    for (DashboardPresenter* dashboard: d->vehicleDashboards.values())
    {
        objectList.append(dashboard);
    }

    this->setViewProperty(PROPERTY(dashboards), QVariant::fromValue(objectList));
}

void ControlPresenter::connectView(QObject* view)
{
    d->map->setView(view->findChild<QObject*>(NAME(map)));

    this->updateVehicles();
}

void ControlPresenter::onVehicleAdded(const db::VehiclePtr& vehicle)
{
    VehicleDashboardFactory factory(d->telemetryService, vehicle);

    DashboardPresenter* dashboard = factory.create();
    if (!dashboard) return;

    d->vehicleDashboards[vehicle->id()] = dashboard;

    this->updateVehicles();
}

void ControlPresenter::onVehicleRemoved(const db::VehiclePtr& vehicle)
{
    d->vehicleDashboards.remove(vehicle->id());
    this->updateVehicles();
}

void ControlPresenter::onVehicleChanged(const db::VehiclePtr& vehicle)
{
    // TODO: updateVehicle();
}

