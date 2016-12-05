#include "mission_presenter.h"

// Internal
#include "vehicle_service.h"
#include "mission_service.h"
#include "vehicle.h"
#include "mission.h"

#include "mission_map_presenter.h"

using namespace presentation;

class MissionPresenter::Impl
{
public:
    MissionMapPresenter* map;
};

MissionPresenter::MissionPresenter(domain::VehicleService* vehicleService,
                                   domain::MissionService* missionService,
                                   QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->map = new MissionMapPresenter(missionService, this);
}

MissionPresenter::~MissionPresenter()
{
    delete d;
}

void MissionPresenter::connectView(QObject* view)
{
    d->map->setView(view->findChild<QObject*>(NAME(map)));
}
