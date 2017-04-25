#include "mission_presenter.h"

// Qt
#include <QVariant>

// Internal
#include "domain_facade.h"

#include "mission_service.h"
#include "mission.h"

using namespace presentation;

class MissionPresenter::Impl
{
public:
    domain::MissionService* missionService;
    db::MissionPtr selectedMission;
};

using namespace presentation;

MissionPresenter::MissionPresenter(domain::DomainFacade* facade,
                                   QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->missionService = facade->missionService();

    connect(d->missionService, &domain::MissionService::missionAdded,
            this, &MissionPresenter::updateMissions);
    connect(d->missionService, &domain::MissionService::missionRemoved,
            this, &MissionPresenter::updateMissions);
}

MissionPresenter::~MissionPresenter()
{}

void MissionPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(selectMission(QString)), this, SLOT(onSelectMission(QString)));
    connect(view, SIGNAL(addMission()), this, SLOT(onAddMission()));
    connect(view, SIGNAL(removeMission()), this, SLOT(onRemoveMission()));

    this->updateMissions();
}

void MissionPresenter::updateMissions()
{
    QStringList missions;
    missions.append(QString());

    for (const db::MissionPtr& mission: d->missionService->missions())
    {
        missions.append(mission->name());
    }
    this->setViewProperty(PROPERTY(missions), QVariant::fromValue(missions));
}

void MissionPresenter::onSelectMission(const QString& name)
{
    if (name.isEmpty())
    {
        d->selectedMission = db::MissionPtr();
    }
    else
    {
        d->selectedMission = d->missionService->findMissionByName(name);
    }
}

void MissionPresenter::onAddMission()
{
    db::MissionPtr mission = db::MissionPtr::create();

    mission->setName(tr("New Mission"));

    d->missionService->saveMission(mission);
    this->setViewProperty(PROPERTY(selectedMission), mission->name());
}

void MissionPresenter::onRemoveMission()
{
    if (d->selectedMission.isNull()) return;

    d->missionService->removeMission(d->selectedMission);
    this->setViewProperty(PROPERTY(selectedMission), QString());
}
