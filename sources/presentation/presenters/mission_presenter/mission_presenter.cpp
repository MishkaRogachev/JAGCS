#include "mission_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "mission_service.h"
#include "mission.h"
#include "mission_vehicle.h"
#include "vehicle_service.h"
#include "abstract_vehicle.h"

#include "mission_map_presenter.h"
#include "mission_view_helper.h"

using namespace presentation;

class MissionPresenter::Impl
{
public:
    domain::MissionService* missionService;
    domain::VehicleService* vehicleService;

    domain::Mission* selectedMission = nullptr;

    QMap<domain::Mission*, QString> missionAliases;
    QMap<domain::AbstractVehicle*, QString> vehicleAliases;

    MissionMapPresenter* map;
    MissionViewHelper helper;
};

MissionPresenter::MissionPresenter(domain::MissionService* missionService,
                                   domain::VehicleService* vehicleService,
                                   QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->missionService = missionService;
    d->vehicleService = vehicleService;

    d->map = new MissionMapPresenter(missionService, vehicleService, this);

    connect(missionService, &domain::MissionService::missionAdded,
            this, &MissionPresenter::updateMissions);
    connect(missionService, &domain::MissionService::missionRemoved,
            this, &MissionPresenter::updateMissions);

    connect(vehicleService, &domain::VehicleService::vehicleAdded,
            this, &MissionPresenter::onVehicleAdded);
    connect(vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &MissionPresenter::onVehicleRemoved);

    for (domain::AbstractVehicle* vehicle: vehicleService->vehicles())
        this->onVehicleAdded(vehicle);
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
    disconnect(m_view, SIGNAL(vehicleSelected(QString)),
               this, SLOT(onVehicleSelected(QString)));

    QStringList vehicleNames = d->vehicleAliases.values();
    vehicleNames.prepend(tr("Unassigned"));
    this->setViewProperty(PROPERTY(vehicleNames), vehicleNames);

    connect(m_view, SIGNAL(vehicleSelected(QString)),
            this, SLOT(onVehicleSelected(QString)));

    if (d->selectedMission) this->updateSelectedVehicle();
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

void MissionPresenter::updateSelectedVehicle()
{
    domain::AbstractVehicle* vehicle = d->selectedMission->assignedVehicle();
    if (vehicle)
    {
        int index = d->vehicleAliases.values().indexOf(
                        d->vehicleAliases[vehicle]) + 1;
        this->setViewProperty(PROPERTY(selectedVehicle), index);
    }
    else
    {
        this->setViewProperty(PROPERTY(selectedVehicle), 0);
    }
}

void MissionPresenter::updateCurrentProgress(int currentProgress)
{
    this->setViewProperty(PROPERTY(currentProgress), currentProgress);
}

void MissionPresenter::updateTotalProgress(int totalProgress)
{
    this->setViewProperty(PROPERTY(totalProgress), totalProgress);
}

void MissionPresenter::connectView(QObject* view)
{
    d->map->setView(view->findChild<QObject*>(NAME(map)));

    this->setViewProperty(PROPERTY(helper), QVariant::fromValue(&d->helper));

    connect(view, SIGNAL(missionSelected(QString)), this, SLOT(onMissionSelected(QString)));
    connect(view, SIGNAL(addMission()), this, SLOT(onAddMission()));
    connect(view, SIGNAL(removeMission()), this, SLOT(onRemoveMission()));

    connect(view, SIGNAL(vehicleSelected(QString)), this, SLOT(onVehicleSelected(QString)));
    connect(view, SIGNAL(downloadMission()), this, SLOT(onDownloadMission()));
    connect(view, SIGNAL(uploadMission()), this, SLOT(onUploadMission()));

    connect(view, SIGNAL(addMissionItem()), this, SLOT(onAddMissionItem()));
    connect(view, SIGNAL(removeMissionItem(QObject*)), this, SLOT(onRemoveMissionItem(QObject*)));

    this->updateMissions();
    this->updateVehicles();
}

void MissionPresenter::onVehicleAdded(domain::AbstractVehicle* vehicle)
{
    d->vehicleAliases[vehicle] = tr("MAV %1").arg(vehicle->vehicleId());

    if (m_view) this->updateVehicles();
}

void MissionPresenter::onVehicleRemoved(domain::AbstractVehicle* vehicle)
{
    d->vehicleAliases.remove(vehicle);

    if (m_view) this->updateVehicles();
}

void MissionPresenter::onMissionSelected(const QString& missionName)
{
    if (d->selectedMission)
    {
        disconnect(d->selectedMission, 0, this, 0);
        disconnect(d->selectedMission->assignment(), 0, this, 0);
    }

    d->selectedMission = d->missionAliases.key(missionName);

    if (d->selectedMission)
    {
        connect(d->selectedMission, &domain::Mission::missionItemsChanged,
                this, &MissionPresenter::updateMissionItems);
        connect(d->selectedMission->assignment(),
                &domain::MissionVehicle::currentProgressChanged,
                this, &MissionPresenter::updateCurrentProgress);
        connect(d->selectedMission->assignment(),
                &domain::MissionVehicle::totalProgressChanged,
                this, &MissionPresenter::updateTotalProgress);

        this->updateCurrentProgress(d->selectedMission->assignment()->currentProgress());
        this->updateTotalProgress(d->selectedMission->assignment()->totalProgress());
        this->updateSelectedVehicle();
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
    if (d->selectedMission) d->selectedMission->removeMissionItem(
                qobject_cast<domain::MissionItem*>(item));
}

void MissionPresenter::onVehicleSelected(const QString& vehicleName)
{
    if (!d->selectedMission) return;

    if (d->vehicleAliases.values().contains(vehicleName))
    {
        d->selectedMission->assignVehicle(d->vehicleAliases.key(vehicleName));
    }
    else
    {
        d->selectedMission->unassignVehicle();
    }
}

void MissionPresenter::onDownloadMission()
{
    if (!d->selectedMission) return;
    d->missionService->downloadMission(d->selectedMission);
}

void MissionPresenter::onUploadMission()
{
    if (!d->selectedMission) return;
    d->missionService->uploadMission(d->selectedMission);
}
