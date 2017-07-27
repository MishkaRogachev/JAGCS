#include "control_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "domain_entry.h"

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
    domain::DomainEntry* entry;

    AbstractMapPresenter* map;
    VideoSplitPresenter* video;
    DashboardPresenter* dashboard = nullptr;
};

ControlPresenter::ControlPresenter(domain::DomainEntry* entry, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->entry = entry;

    domain::VehicleService* service = entry->vehicleService();

    d->map = new LocationMapPresenter(entry, this);
    d->video = new VideoSplitPresenter(entry->videoService(), this);

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

    for (const dao::VehiclePtr& vehicle: d->entry->vehicleService()->vehicles())
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
    dao::VehiclePtrList vehicles  = d->entry->vehicleService()->vehicles();

    if (d->dashboard) delete d->dashboard;

    if (index > 0 && index <= vehicles.count())
    {
        dao::VehiclePtr vehicle = vehicles[index - 1];

        AerialDashboardFactory factory(d->entry, vehicle);
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
    }
}


