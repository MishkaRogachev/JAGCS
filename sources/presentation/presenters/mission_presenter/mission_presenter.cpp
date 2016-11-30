#include "mission_presenter.h"

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

#include "vehicle_map_presenter.h"

using namespace presentation;

class MissionPresenter::Impl
{
public:
    domain::VehicleService* vehicleService;

    VehicleMapPresenter* map;
};

MissionPresenter::MissionPresenter(domain::VehicleService* vehicleService,
                                   QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->vehicleService = vehicleService;

    d->map = new VehicleMapPresenter(vehicleService, this);
}

MissionPresenter::~MissionPresenter()
{
    delete d;
}

void MissionPresenter::connectView(QObject* view)
{
    d->map->setView(view->findChild<QObject*>(NAME(map)));
}
