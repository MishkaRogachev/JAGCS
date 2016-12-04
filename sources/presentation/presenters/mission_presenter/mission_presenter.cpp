#include "mission_presenter.h"

// Internal
#include "vehicle_service.h"
#include "mission_service.h"
#include "vehicle.h"
#include "mission.h"

#include "vehicle_map_presenter.h"
#include "mission_map_item_model.h"

using namespace presentation;

class MissionPresenter::Impl
{
public:
    domain::VehicleService* vehicleService;
    domain::MissionService* missionService;

    VehicleMapPresenter* map;
    MissionMapItemModel missionModel;

    Impl(domain::VehicleService* vehicleService,
         domain::MissionService* missionService):
        vehicleService(vehicleService),
        missionService(missionService),
        missionModel(missionService)
    {}
};

MissionPresenter::MissionPresenter(domain::VehicleService* vehicleService,
                                   domain::MissionService* missionService,
                                   QObject* object):
    BasePresenter(object),
    d(new Impl(vehicleService, missionService))
{
    d->map = new VehicleMapPresenter(vehicleService, this);
}

MissionPresenter::~MissionPresenter()
{
    delete d;
}

void MissionPresenter::connectView(QObject* view)
{
    d->map->setView(view->findChild<QObject*>(NAME(map)));

    this->setViewProperty(PROPERTY(missionModel),
                          QVariant::fromValue(&d->missionModel));
}
