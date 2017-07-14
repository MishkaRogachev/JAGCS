#include "planning_presenter.h"

// Internal
#include "domain_entry.h"

#include "mission_presenter.h"
#include "location_map_presenter.h"
#include "vertical_profile_presenter.h"

#include "mission.h"

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

PlanningPresenter::PlanningPresenter(domain::DomainEntry* entry, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->mission = new MissionPresenter(entry, this);
    d->map = new LocationMapPresenter(entry, this);
    d->profile = new VerticalProfilePresenter(entry->dbFacade(), this);

    connect(d->mission, &MissionPresenter::missionSelected,
            d->profile, &VerticalProfilePresenter::selectMission);
}

void PlanningPresenter::connectView(QObject* view)
{
    d->mission->setView(view->findChild<QObject*>(NAME(mission)));
    d->map->setView(view->findChild<QObject*>(NAME(map)));
    d->profile->setView(view->findChild<QObject*>(NAME(profile)));
}

PlanningPresenter::~PlanningPresenter()
{}
