#include "combat_presenter.h"

// Internal
#include "location_map_presenter.h"

using namespace presentation;

class CombatPresenter::Impl
{
public:
    AbstractMapPresenter* map;
};

CombatPresenter::CombatPresenter(domain::DomainEntry* entry, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->map = new LocationMapPresenter(entry, this);
}

CombatPresenter::~CombatPresenter()
{}

void CombatPresenter::connectView(QObject* view)
{
    d->map->setView(view->findChild<QObject*>(NAME(map)));
}
