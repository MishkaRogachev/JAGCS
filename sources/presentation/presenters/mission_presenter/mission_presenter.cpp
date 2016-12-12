#include "mission_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "mission_service.h"
#include "mission.h"

#include "mission_map_presenter.h"

using namespace presentation;

class MissionPresenter::Impl
{
public:
    domain::MissionService* missionService;
    domain::Mission* selectedMission = nullptr;

    QMap<uint8_t, QString> missionAliases;

    MissionMapPresenter* map;
};

MissionPresenter::MissionPresenter(domain::MissionService* missionService,
                                   QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->missionService = missionService;

    d->map = new MissionMapPresenter(missionService, this);

    connect(missionService, &domain::MissionService::missionAdded,
            this, &MissionPresenter::updateMissions);
    connect(missionService, &domain::MissionService::missionRemoved,
            this, &MissionPresenter::updateMissions);
}

MissionPresenter::~MissionPresenter()
{
    delete d;
}

void MissionPresenter::updateMissions()
{
    d->missionAliases.clear();

    for (uint8_t id: d->missionService->missionIds())
        d->missionAliases[id] = tr("Mission") + " " + QString::number(id);

    QStringList missionNames = d->missionAliases.values();
    this->setViewProperty(PROPERTY(missionNames), missionNames);
}

void MissionPresenter::updateMissionItems()
{
    QObjectList list;

    if (d->selectedMission)
    {
        for (domain::MissionItem* item: d->selectedMission->items())
            list.append(item);
    }

    this->setViewProperty(PROPERTY(missionItems), QVariant::fromValue(list));
}

void MissionPresenter::connectView(QObject* view)
{
    d->map->setView(view->findChild<QObject*>(NAME(map)));

    connect(view, SIGNAL(missionSelected(QString)),
            this, SLOT(onMissionSelected(QString)));
    connect(view, SIGNAL(addMissionItem()), this, SLOT(onAddMissionItem()));
    connect(view, SIGNAL(removeMissionItem(QObject*)),
            this, SLOT(onRemoveMissionItem(QObject*)));

    this->updateMissions();
}

void MissionPresenter::onMissionSelected(const QString& missionName)
{
    if (d->selectedMission)
    {
        disconnect(d->selectedMission, 0, this, 0);
    }

    d->selectedMission =
            d->missionService->mission(d->missionAliases.key(missionName));

    if (d->selectedMission)
    {
        connect(d->selectedMission, &domain::Mission::missionItemAdded,
                this, &MissionPresenter::updateMissionItems);
        connect(d->selectedMission, &domain::Mission::missionItemRemoved,
                this, &MissionPresenter::updateMissionItems);
    }
    this->updateMissionItems();
}

void MissionPresenter::onAddMissionItem()
{
    if (d->selectedMission) d->selectedMission->addNewMissionItem();
}

void MissionPresenter::onRemoveMissionItem(QObject* item)
{
    if (d->selectedMission) d->selectedMission->removeMissionItem(
                qobject_cast<domain::MissionItem*>(item));
}
