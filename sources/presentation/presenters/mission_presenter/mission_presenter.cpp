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

void MissionPresenter::connectView(QObject* view)
{
    d->map->setView(view->findChild<QObject*>(NAME(map)));

    connect(view, SIGNAL(missionSelected(QString)),
            this, SLOT(onMissionSelected(QString)));

    this->updateMissions();
}

void MissionPresenter::onMissionSelected(const QString& missionName)
{
    domain::Mission* mission = d->missionService->mission(
                                   d->missionAliases.key(missionName));
    if (!mission) return;

    QObjectList list;

    for (domain::MissionItem* item: mission->items())
        list.append(item);

    this->setViewProperty(PROPERTY(missionItems), QVariant::fromValue(list));
}
