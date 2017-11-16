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

     QMap<int, MissionPresenter*> missionPresenters;
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
        d->missionPresenters[mission->id()] = new MissionPresenter(mission, this);
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
    this->updateMissions();
}

void MissionListPresenter::onMissionAdded(const dao::MissionPtr& mission)
{
    if (d->missionPresenters.contains(mission->id())) return;

    d->missionPresenters[mission->id()] = new MissionPresenter(mission, this);
    this->updateMissions();
}

void MissionListPresenter::onMissionRemoved(const dao::MissionPtr& mission)
{
    if (!d->missionPresenters.contains(mission->id())) return;

    delete d->missionPresenters.take(mission->id());
    this->updateMissions();
}

void MissionListPresenter::onMissionChanged(const dao::MissionPtr& mission)
{
    if (!d->missionPresenters.contains(mission->id())) return;

    d->missionPresenters[mission->id()]->updateView();
}
