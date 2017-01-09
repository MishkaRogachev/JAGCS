#include "mission_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "mission_service.h"
#include "mission.h"
#include "vehicle_service.h"
#include "vehicle.h"

#include "mission_map_presenter.h"

using namespace presentation;

class MissionPresenter::Impl
{
public:
    domain::MissionService* missionService;
    domain::VehicleService* vehicleService;

    domain::Mission* selectedMission = nullptr;

    QMap<domain::Mission*, QString> missionAliases;
    QMap<uint8_t, QString> vehicleAliases;

    MissionMapPresenter* map;
};

MissionPresenter::MissionPresenter(domain::MissionService* missionService,
                                   domain::VehicleService* vehicleService,
                                   QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->missionService = missionService;
    d->vehicleService = vehicleService;

    connect(missionService, &domain::MissionService::missionAdded,
            this, &MissionPresenter::updateMissions);
    connect(missionService, &domain::MissionService::missionRemoved,
            this, &MissionPresenter::updateMissions);

    connect(missionService, &domain::MissionService::currentCountChanged,
            this, &MissionPresenter::updateCurrentCount);
    connect(missionService, &domain::MissionService::totalCountChanged,
            this, &MissionPresenter::updateTotalCount);

    connect(vehicleService, &domain::VehicleService::vehicleAdded,
            this, &MissionPresenter::onVehicleAdded);
    connect(vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &MissionPresenter::onVehicleRemoved);

    for (uint8_t id: vehicleService->vehileIds())
        this->onVehicleAdded(id);

    d->map = new MissionMapPresenter(missionService, this);
}

MissionPresenter::~MissionPresenter()
{
    delete d;
}

void MissionPresenter::updateMissions()
{
    d->missionAliases.clear();

    int id = 0;
    for (domain::Mission* mission: d->missionService->missions())
    {
        d->missionAliases[mission] = tr("Mission") + " " + QString::number(id++);
    }

    QStringList missionNames = d->missionAliases.values();
    this->setViewProperty(PROPERTY(missionNames), missionNames);
}

void MissionPresenter::updateVehicles()
{
    QStringList vehicleNames = d->vehicleAliases.values();
    this->setViewProperty(PROPERTY(vehicleNames), vehicleNames);
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

void MissionPresenter::updateCurrentCount(int currentCount)
{
    this->setViewProperty(PROPERTY(currentCount), currentCount);
}

void MissionPresenter::updateTotalCount(int totalCount)
{
    this->setViewProperty(PROPERTY(totalCount), totalCount);
}

void MissionPresenter::connectView(QObject* view)
{
    d->map->setView(view->findChild<QObject*>(NAME(map)));

    connect(view, SIGNAL(missionSelected(QString)), this, SLOT(onMissionSelected(QString)));
    connect(view, SIGNAL(addMission()), this, SLOT(onAddMission()));
    connect(view, SIGNAL(removeMission()), this, SLOT(onRemoveMission()));
    connect(view, SIGNAL(addMissionItem()), this, SLOT(onAddMissionItem()));
    connect(view, SIGNAL(removeMissionItem(QObject*)), this, SLOT(onRemoveMissionItem(QObject*)));
    connect(view, SIGNAL(downloadMission(QString)), this, SLOT(onDownloadMission(QString)));
    connect(view, SIGNAL(uploadMission(QString)), this, SLOT(onUploadMission(QString)));

    this->updateMissions();
    this->updateVehicles();

    this->updateCurrentCount(d->missionService->currentCount());
    this->updateTotalCount(d->missionService->totalCount());
}

void MissionPresenter::onVehicleAdded(uint8_t id)
{
    d->vehicleAliases[id] = tr("MAV %1").arg(id);

    if (m_view) this->updateVehicles();
}

void MissionPresenter::onVehicleRemoved(uint8_t id)
{
    d->vehicleAliases.remove(id);

    if (m_view) this->updateVehicles();
}

void MissionPresenter::onMissionSelected(const QString& missionName)
{
    if (d->selectedMission)
    {
        disconnect(d->selectedMission, 0, this, 0);
    }

    d->selectedMission = d->missionAliases.key(missionName);

    if (d->selectedMission)
    {
        connect(d->selectedMission, &domain::Mission::missionItemsChanged,
                this, &MissionPresenter::updateMissionItems);
    }
    this->updateMissionItems();
}

void MissionPresenter::onAddMission()
{
    d->missionService->addNewMission();
}

void MissionPresenter::onRemoveMission()
{
    if (!d->selectedMission) return;

    d->missionService->deleteMission(d->selectedMission);
}

void MissionPresenter::onAddMissionItem()
{
    if (d->selectedMission) d->selectedMission->addNewMissionItem();
}

void MissionPresenter::onRemoveMissionItem(QObject* item)
{
    if (d->selectedMission) d->selectedMission->deleteMissionItem(
                qobject_cast<domain::MissionItem*>(item));
}

void MissionPresenter::onDownloadMission(const QString& vehicleName)
{
    uint8_t vehicleId = d->vehicleAliases.key(vehicleName);

    if (d->selectedMission)
    {
        d->missionService->setVehicleForMission(vehicleId, d->selectedMission);
    }

    d->missionService->commandDownloadMission(vehicleId);
}

void MissionPresenter::onUploadMission(const QString& vehicleName)
{
    if (!d->selectedMission) return;

    uint8_t vehicleId = d->vehicleAliases.key(vehicleName);

    d->missionService->setVehicleForMission(vehicleId, d->selectedMission);
    d->missionService->commandUploadMission(vehicleId);
}
