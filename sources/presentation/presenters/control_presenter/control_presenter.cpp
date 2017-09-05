#include "control_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "vehicle_service.h"
#include "vehicle.h"

#include "telemetry_service.h"

#include "vehicle_type_mapper.h"
#include "location_map_presenter.h"
#include "video_split_presenter.h"

#include "dashboard_presenter.h"
#include "aerial_dashboard_factory.h"

using namespace presentation;

class ControlPresenter::Impl
{
public:
    AbstractMapPresenter* map;
    VideoSplitPresenter* video;
    DashboardPresenter* dashboard = nullptr;
};

ControlPresenter::ControlPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    domain::VehicleService* service = domain::ServiceRegistry::vehicleService();

    d->map = new LocationMapPresenter(this);
    d->video = new VideoSplitPresenter(this);

    connect(service, &domain::VehicleService::vehicleAdded, this, &ControlPresenter::updateVehiclesList);
    connect(service, &domain::VehicleService::vehicleRemoved, this, &ControlPresenter::updateVehiclesList);
}

ControlPresenter::~ControlPresenter()
{}

void ControlPresenter::updateVehiclesList()
{
    QStringList vehicles;
    vehicles.append(QString());
    int index = 1;
    int onlineIndex = -1;

    for (const dao::VehiclePtr& vehicle: domain::ServiceRegistry::vehicleService()->vehicles())
    {
        vehicles.append(vehicle->name());
        if (vehicle->isOnline() && onlineIndex == -1) onlineIndex = index;
        index++;
    }

    this->setViewProperty(PROPERTY(vehicles), vehicles);
    if (onlineIndex > -1) this->setViewProperty(PROPERTY(selectedVehicle), onlineIndex);
}

void ControlPresenter::connectView(QObject* view)
{
    d->map->setView(view->findChild<QObject*>(NAME(map)));
    d->video->setView(view->findChild<QObject*>(NAME(video)));

    connect(view, SIGNAL(selectVehicle(int)), this, SLOT(onSelectVehicle(int)));

    this->updateVehiclesList();
}

void ControlPresenter::onSelectVehicle(int index)
{
    // TODO: check, if vehicle is the same
    dao::VehiclePtrList vehicles  = domain::ServiceRegistry::vehicleService()->vehicles();

    if (d->dashboard) delete d->dashboard;

    if (index > 0 && index <= vehicles.count())
    {
        dao::VehiclePtr vehicle = vehicles[index - 1];
        d->map->selectVehicle(vehicle);

        AerialDashboardFactory factory(vehicle);
        d->dashboard = factory.create();

        if (d->dashboard)
        {
            d->dashboard->setParent(this);
            d->dashboard->setView(this->view()->findChild<QObject*>(NAME(dashboard)));
            d->dashboard->setViewProperty(PROPERTY(vehicleMark), ::vehicleIcon(vehicle->type()));
        }
    }
    else
    {
        d->dashboard = nullptr;
        d->map->selectVehicle(dao::VehiclePtr());
    }
}


