#include "planning_presenter.h"

// Internal
#include "mission_presenter.h"
#include "location_map_presenter.h"

using namespace presentation;

using namespace presentation;

class PlanningPresenter::Impl
{
public:
    MissionPresenter* mission;
    AbstractMapPresenter* map;
};

using namespace presentation;

PlanningPresenter::PlanningPresenter(domain::DomainEntry* entry, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->mission = new MissionPresenter(entry, this);
    d->map = new LocationMapPresenter(entry, this);
}

void PlanningPresenter::connectView(QObject* view)
{
    d->mission->setView(view->findChild<QObject*>(NAME(mission)));
    d->map->setView(view->findChild<QObject*>(NAME(map)));
}

PlanningPresenter::~PlanningPresenter()
{
    if (d->map->view()) d->map->saveViewPort();
}
