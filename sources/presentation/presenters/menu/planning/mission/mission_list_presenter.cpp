#include "mission_list_presenter.h"

// Qt
#include <QVariant>
#include <QMap>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "mission.h"

#include "service_registry.h"
#include "mission_service.h"

#include "mission_presenter.h"

using namespace presentation;

class MissionListPresenter::Impl
{
public:
    domain::MissionService* service = domain::ServiceRegistry::missionService();

     QMap<dao::MissionPtr, MissionPresenter*> missionPresenters;
};

MissionListPresenter::MissionListPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    connect(d->service, &domain::MissionService::missionAdded,
            this, &MissionListPresenter::onMissionAdded);
    connect(d->service, &domain::MissionService::missionRemoved,
            this, &MissionListPresenter::onMissionRemoved);
    connect(d->service, &domain::MissionService::missionChanged,
            this, &MissionListPresenter::onMissionChanged);

    for (const dao::MissionPtr& mission: d->service->missions())
    {
        d->missionPresenters[mission] = new MissionPresenter(mission, this);
    }
}

MissionListPresenter::~MissionListPresenter()
{}

void MissionListPresenter::updateMissions()
{
    QObjectList objectList;
    for (MissionPresenter* missionPresenter: d->missionPresenters.values())
    {
        objectList.append(missionPresenter);
    }

    this->setViewProperty(PROPERTY(missions), QVariant::fromValue(objectList));
}

void MissionListPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(addMission()), this, SLOT(onAddMission()));

    this->updateMissions();
}

void MissionListPresenter::onMissionAdded(const dao::MissionPtr& mission)
{
    if (d->missionPresenters.contains(mission)) return;

    d->missionPresenters[mission] = new MissionPresenter(mission, this);
    this->updateMissions();
}

void MissionListPresenter::onMissionRemoved(const dao::MissionPtr& mission)
{
    if (!d->missionPresenters.contains(mission)) return;

    delete d->missionPresenters.take(mission);
    this->updateMissions();
}

void MissionListPresenter::onMissionChanged(const dao::MissionPtr& mission)
{
    if (!d->missionPresenters.contains(mission)) return;

    d->missionPresenters[mission]->updateView();
}

void MissionListPresenter::onAddMission()
{
    dao::MissionPtr mission = dao::MissionPtr::create();
    mission->setName(tr("New Mission"));

    d->service->save(mission);
}
