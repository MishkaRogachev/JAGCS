#include "planning_presenter.h"

// Internal
#include "service_registry.h"

#include "mission_presenter.h"
#include "location_map_presenter.h"
#include "vertical_profile_presenter.h"

#include "mission.h"
#include "mission_item.h"

using namespace presentation;

using namespace presentation;

class PlanningPresenter::Impl
{
public:
    MissionPresenter* mission;
    AbstractMapPresenter* map;
    VerticalProfilePresenter* profile;
};

using namespace presentation;

PlanningPresenter::PlanningPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->mission = new MissionPresenter(this);
    d->map = new LocationMapPresenter(this);
    d->profile = new VerticalProfilePresenter(this);

    connect(d->mission, &MissionPresenter::missionSelected,
            d->profile, &VerticalProfilePresenter::selectMission);
    connect(d->mission, &MissionPresenter::missionItemSelected,
            d->map, &AbstractMapPresenter::selectMissionItem);
    connect(d->map, &AbstractMapPresenter::missionItemSelected,
            d->mission, &MissionPresenter::selectMissionItem);
}

void PlanningPresenter::connectView(QObject* view)
{
    d->mission->setView(view->findChild<QObject*>(NAME(mission)));
    d->map->setView(view->findChild<QObject*>(NAME(map)));
    d->profile->setView(view->findChild<QObject*>(NAME(profile)));
}

PlanningPresenter::~PlanningPresenter()
{}
