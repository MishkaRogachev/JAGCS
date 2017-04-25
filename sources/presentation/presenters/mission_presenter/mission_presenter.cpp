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
    connect(view, SIGNAL(renameMission(QString)), this, SLOT(onRenameMission(QString)));

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
    this->setViewProperty(PROPERTY(selectedMission), d->selectedMission.isNull() ?
                              QString() : d->selectedMission->name());
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

    mission->setName(tr("New Mission %1").arg(
                         d->missionService->missions().count()));

    d->missionService->saveMission(mission);
    d->selectedMission = mission;
}

void MissionPresenter::onRemoveMission()
{
    if (d->selectedMission.isNull()) return;

    d->missionService->removeMission(d->selectedMission);
    d->selectedMission.clear();
}

void MissionPresenter::onRenameMission(const QString& name)
{
    if (d->selectedMission.isNull()) return;

    d->selectedMission->setName(name);
    d->missionService->saveMission(d->selectedMission);
    this->updateMissions();
}
