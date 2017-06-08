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

    connect(d->dbFacade, &db::DbFacade::vehicleAdded, this, &ControlPresenter::updateVehiclesList);
    connect(d->dbFacade, &db::DbFacade::vehicleRemoved, this, &ControlPresenter::updateVehiclesList);
    connect(d->dbFacade, &db::DbFacade::vehicleChanged, this, &ControlPresenter::updateVehiclesList);

    this->updateVehiclesList();
}

ControlPresenter::~ControlPresenter()
{}

void ControlPresenter::updateVehiclesList()
{
    QStringList vehicles;
    vehicles.append(QString());

    for (const db::VehiclePtr& vehicle: d->dbFacade->vehicles())
    {
        vehicles.append(vehicle->name());
    }

    this->setViewProperty(PROPERTY(vehicles), vehicles);
}

void ControlPresenter::connectView(QObject* view)
{
    d->map->setView(view->findChild<QObject*>(NAME(map)));

    connect(view, SIGNAL(selectVehicle(int)),
            this, SLOT(onSelectVehicle(int)));

    this->updateVehiclesList();
}

void ControlPresenter::onSelectVehicle(int index)
{
    db::VehiclePtrList vehicles  = d->dbFacade->vehicles();

    if (index > 0 && index <= vehicles.count())
    {
        qDebug() << vehicles[index - 1]->name(); // TODO: select
    }
    else
    {
        // TODO: unselect
    }
}


