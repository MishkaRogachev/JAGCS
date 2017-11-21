#include "mission_list_presenter.h"

// Qt
#include <QVariant>
#include <QMap>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "mission.h"
#include "mission_assignment.h"

#include "service_registry.h"
#include "mission_service.h"

#include "mission_presenter.h"

using namespace presentation;

class MissionListPresenter::Impl
{
public:
    domain::MissionService* service = domain::ServiceRegistry::missionService();

    QMap<int, MissionPresenter*> missions;
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

    connect(d->service, &domain::MissionService::assignmentAdded,
            this, &MissionListPresenter::updateMissionAssignment);
    connect(d->service, &domain::MissionService::assignmentRemoved,
            this, &MissionListPresenter::updateMissionAssignment);
    connect(d->service, &domain::MissionService::assignmentChanged,
            this, &MissionListPresenter::updateMissionAssignment);

    for (const dao::MissionPtr& mission: d->service->missions())
    {
        d->missions[mission->id()] = new MissionPresenter(mission, this);
    }
}

MissionListPresenter::~MissionListPresenter()
{}

void MissionListPresenter::updateMissions()
{
    QObjectList objectList;
    for (MissionPresenter* missionPresenter: d->missions.values())
    {
        objectList.append(missionPresenter);
    }

    this->setViewProperty(PROPERTY(missions), QVariant::fromValue(objectList));
}

void MissionListPresenter::addMission()
{
    dao::MissionPtr mission = dao::MissionPtr::create();
    mission->setName(tr("New Mission"));

    d->service->save(mission);
}

void MissionListPresenter::onMissionAdded(const dao::MissionPtr& mission)
{
    if (d->missions.contains(mission->id())) return;

    d->missions[mission->id()] = new MissionPresenter(mission, this);
    this->updateMissions();
}

void MissionListPresenter::onMissionRemoved(const dao::MissionPtr& mission)
{
    if (!d->missions.contains(mission->id())) return;

    delete d->missions.take(mission->id());
    this->updateMissions();
}

void MissionListPresenter::onMissionChanged(const dao::MissionPtr& mission)
{
    if (!d->missions.contains(mission->id())) return;

    d->missions[mission->id()]->updateMission();
}

void MissionListPresenter::updateMissionAssignment(const dao::MissionAssignmentPtr& assignment)
{
    if (!d->missions.contains(assignment->missionId())) return;

    d->missions[assignment->missionId()]->updateAssignment();
}
