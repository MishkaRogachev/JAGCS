#include "control_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "service_registry.h"
#include "vehicle_service.h"
#include "vehicle.h"

#include "telemetry_service.h"

#include "joystick_manager.h"

#include "vehicle_type_mapper.h"
#include "location_map_presenter.h"
#include "video_split_presenter.h"

#include "dashboard_presenter.h"
#include "aerial_dashboard_factory.h"
#include "command_presenter.h"

using namespace presentation;

class ControlPresenter::Impl
{
public:
    domain::JoystickManager* joystick = nullptr;

    AbstractMapPresenter* map;
    VideoSplitPresenter* video;
    CommandPresenter* command;
    DashboardPresenter* dashboard = nullptr;
};

ControlPresenter::ControlPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    if (settings::Provider::value(settings::joystick::enabled).toBool())
    {
        d->joystick = new domain::JoystickManager(this);
    }

    d->map = new LocationMapPresenter(this);
    d->video = new VideoSplitPresenter(this);
    d->command = new CommandPresenter(this);

    domain::VehicleService* service = domain::ServiceRegistry::vehicleService();
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
    d->command->setView(view->findChild<QObject*>(NAME(command)));
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
        d->command->setControlVehicle(vehicle->id());

        AerialDashboardFactory factory(vehicle);
        d->dashboard = factory.create();

        if (d->dashboard)
        {
            d->dashboard->setParent(this);
            d->dashboard->setView(this->view()->findChild<QObject*>(NAME(dashboard)));
            d->dashboard->setViewProperty(PROPERTY(vehicleMark), ::vehicleIcon(vehicle->type()));
        }

        if (d->joystick) d->joystick->setControlVehicle(vehicle->id());
    }
    else
    {
        d->dashboard = nullptr;
        d->map->selectVehicle(dao::VehiclePtr());

        d->command->setControlVehicle(0);

        if (d->joystick) d->joystick->setControlVehicle(0);
    }
}


