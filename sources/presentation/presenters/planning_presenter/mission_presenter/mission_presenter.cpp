#include "mission_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "mission.h"
#include "mission_item.h"
#include "mission_assignment.h"
#include "vehicle.h"

#include "service_registry.h"
#include "mission_service.h"
#include "vehicle_service.h"
#include "command_service.h"

#include "mission_items_status_presenter.h"
#include "mission_item_edit_presenter.h"

using namespace presentation;

class MissionPresenter::Impl
{
public:
    domain::VehicleService* vehicleService = domain::ServiceRegistry::vehicleService();
    domain::MissionService* missionService = domain::ServiceRegistry::missionService();

    dao::MissionPtr selectedMission;
    dao::MissionPtrList missions;

    MissionItemsStatusPresenter* itemsStatus;
    MissionItemEditPresenter* itemEdit;
};

using namespace presentation;

MissionPresenter::MissionPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->itemsStatus = new MissionItemsStatusPresenter(this);
    d->itemEdit = new MissionItemEditPresenter(this);

    connect(d->itemEdit, &MissionItemEditPresenter::itemSelected,
            this, &MissionPresenter::missionItemSelected);
    connect(d->itemEdit, &MissionItemEditPresenter::itemSelected,
            d->itemsStatus, &MissionItemsStatusPresenter::selectMissionItem);

    connect(d->itemsStatus, &MissionItemsStatusPresenter::selectItem,
            d->itemEdit, &MissionItemEditPresenter::selectItem);
    connect(d->itemsStatus, &MissionItemsStatusPresenter::holded,
            d->itemEdit, &MissionItemEditPresenter::enablePicker);

    d->missions.append(d->missionService->missions());

    connect(d->missionService, &domain::MissionService::missionAdded,
            this, &MissionPresenter::onMissionAdded);
    connect(d->missionService, &domain::MissionService::missionRemoved,
            this, &MissionPresenter::onMissionRemoved);
    connect(d->missionService, &domain::MissionService::missionChanged,
            this, &MissionPresenter::onMissionChanged);

    connect(d->missionService, &domain::MissionService::assignmentAdded,
            this, &MissionPresenter::updateAssignment);
    connect(d->missionService, &domain::MissionService::assignmentRemoved,
            this, &MissionPresenter::updateAssignment);
    connect(d->missionService, &domain::MissionService::assignmentChanged,
            this, &MissionPresenter::updateAssignment);

    connect(d->vehicleService, &domain::VehicleService::vehicleAdded,
            this, &MissionPresenter::updateVehiclesBox);
    connect(d->vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &MissionPresenter::updateVehiclesBox);
}

MissionPresenter::~MissionPresenter()
{}

void MissionPresenter::selectMission(const dao::MissionPtr& mission)
{
    if (d->selectedMission == mission) return;

    d->selectedMission = mission;

    d->itemsStatus->selectMission(mission);
    d->itemEdit->selectMission(mission);

    this->setViewProperty(PROPERTY(selectedMission), d->missions.indexOf(d->selectedMission) + 1);

    if (mission)
    {
        this->setViewProperty(PROPERTY(missionVisible),
                              settings::Provider::value(settings::mission::visibility + "/" + mission->id()));
    }
    else this->setViewProperty(PROPERTY(missionVisible), false);

    this->updateAssignment();

    emit missionSelected(mission);
}

void MissionPresenter::selectMissionItem(const dao::MissionItemPtr& item)
{
    if (!item) return;

    this->selectMission(d->missionService->mission(item->missionId()));

    d->itemEdit->selectItem(item->sequence());
}

void MissionPresenter::enablePicker()
{
    d->itemEdit->enablePicker();
}

void MissionPresenter::connectView(QObject* view)
{
    d->itemsStatus->setView(view->findChild<QObject*>(NAME(itemsStatus)));
    d->itemEdit->setView(view->findChild<QObject*>(NAME(itemEdit)));

    this->updateVehiclesBox();
    this->updateMissionsBox();
}

void MissionPresenter::setViewConnected(bool connected)
{
    if (connected)
    {
        connect(this->view(), SIGNAL(selectMission(int)), this, SLOT(onSelectMission(int)));
        connect(this->view(), SIGNAL(addMission()), this, SLOT(onAddMission()));
        connect(this->view(), SIGNAL(addItem()), this, SLOT(onAddItem()));
        connect(this->view(), SIGNAL(removeMission()), this, SLOT(onRemoveMission()));
        connect(this->view(), SIGNAL(renameMission(QString)), this, SLOT(onRenameMission(QString)));
        connect(this->view(), SIGNAL(assignVehicle(int)), this, SLOT(onAssignVehicle(int)));
        connect(this->view(), SIGNAL(setMissionVisible(bool)), this, SLOT(onSetMissionVisible(bool)));
        connect(this->view(), SIGNAL(uploadMission()), this, SLOT(onUploadMission()));
        connect(this->view(), SIGNAL(downloadMission()), this, SLOT(onDownloadMission()));
        connect(this->view(), SIGNAL(cancelSyncMission()), this, SLOT(onCancelSyncMission()));
    }
    else
    {
        disconnect(this->view(), 0, this, 0);
    }
}

void MissionPresenter::onMissionAdded(const dao::MissionPtr& mission)
{
    d->missions.append(mission);
    this->updateMissionsBox();
}

void MissionPresenter::onMissionRemoved(const dao::MissionPtr& mission)
{
    d->missions.removeOne(mission);
    this->updateMissionsBox();
}

void MissionPresenter::onMissionChanged(const dao::MissionPtr& mission)
{
    Q_UNUSED(mission)

    this->updateMissionsBox();
}

void MissionPresenter::updateMissionsBox()
{
    this->setViewConnected(false);

    QStringList missions;
    missions.append(QString());

    for (const dao::MissionPtr& mission: d->missions)
    {
        missions.append(mission->name());
    }
    this->setViewProperty(PROPERTY(missions), QVariant::fromValue(missions));
    this->setViewProperty(PROPERTY(selectedMission), d->missions.indexOf(d->selectedMission) + 1);
    this->setViewConnected(true);
}

void MissionPresenter::updateVehiclesBox()
{
    this->setViewConnected(false);

    QStringList vehicles;
    vehicles.append(QString());

    for (const dao::VehiclePtr& vehicle: d->vehicleService->vehicles())
    {
        vehicles.append(vehicle->name());
    }
    this->setViewProperty(PROPERTY(vehicles), QVariant::fromValue(vehicles));
    this->setViewConnected(true);

    this->updateAssignment();
}

void MissionPresenter::updateAssignment()
{
    this->setViewConnected(false);

    if (d->selectedMission)
    {
        dao::MissionAssignmentPtr assignment =
                d->missionService->missionAssignment(d->selectedMission->id());
        if (assignment)
        {
            dao::VehiclePtr vehicle = d->vehicleService->vehicle(assignment->vehicleId());
            if (vehicle)
            {
                this->setViewProperty(PROPERTY(assignedVehicle),
                                      d->vehicleService->vehicles().indexOf(vehicle) + 1);
            }

            this->setViewProperty(PROPERTY(status), assignment->status());
            this->setViewConnected(true);
            return;
        }
    }
    this->setViewProperty(PROPERTY(assignedVehicle), 0);

    this->setViewProperty(PROPERTY(status), dao::MissionAssignment::NotActual);

    this->setViewConnected(true);
}

void MissionPresenter::onSelectMission(int index)
{
    if (index > 0 && index < d->missions.count() + 1)
    {
        this->selectMission(d->missions.at(index - 1));
    }
    else
    {
        this->selectMission(dao::MissionPtr());
    }
}

void MissionPresenter::onAddMission()
{
    dao::MissionPtr mission = dao::MissionPtr::create();

    mission->setName(tr("New Mission %1").arg(d->missionService->missions().count()));

    d->missionService->save(mission);
    this->selectMission(mission);
}

void MissionPresenter::onAddItem()
{
    if (d->selectedMission.isNull()) return;

    d->missionService->addNewMissionItem(d->selectedMission->id());
    d->itemEdit->selectItem(d->selectedMission->count() - 1);
    d->itemEdit->enablePicker();
}

void MissionPresenter::onRemoveMission()
{
    if (d->selectedMission.isNull()) return;

    d->missionService->remove(d->selectedMission);
    d->selectedMission.clear();
    this->setViewProperty(PROPERTY(selectedMission), 0);

    d->itemEdit->selectMission(dao::MissionPtr());
}

void MissionPresenter::onRenameMission(const QString& name)
{
    if (d->selectedMission.isNull() || name.isEmpty()) return;

    // TODO: check unique name
    d->selectedMission->setName(name);
    d->missionService->save(d->selectedMission);
    this->updateMissionsBox();
}

void MissionPresenter::onAssignVehicle(int index) // TODO: AssignmentPresenter and View
{
    // TODO: fix vehicle assignment
    if (!d->selectedMission) return;

    dao::VehiclePtrList vehicles = d->vehicleService->vehicles();
    dao::VehiclePtr vehicle = (index > 0 && index <= vehicles.count()) ?
                                 vehicles.at(index - 1) : dao::VehiclePtr();

    if (vehicle)
    {
        d->missionService->assign(d->selectedMission->id(), vehicle->id());
    }
    else
    {
        d->missionService->unassign(d->selectedMission->id());
    }
}

void MissionPresenter::onSetMissionVisible(bool visible)
{
    if (!d->selectedMission) return;

    settings::Provider::setValue(settings::mission::visibility + "/" +
                                 d->selectedMission->id(), visible);
    this->setViewProperty(PROPERTY(missionVisible), visible);

    d->missionService->missionChanged(d->selectedMission);
}

void MissionPresenter::onUploadMission()
{
    if (!d->selectedMission) return;
    dao::MissionAssignmentPtr assignment = d->missionService->missionAssignment(d->selectedMission->id());
    if (assignment.isNull()) return;

    d->missionService->upload(assignment);
}

void MissionPresenter::onDownloadMission()
{
    if (!d->selectedMission) return;
    dao::MissionAssignmentPtr assignment = d->missionService->missionAssignment(d->selectedMission->id());
    if (assignment.isNull()) return;

    d->missionService->download(assignment);
}

void MissionPresenter::onCancelSyncMission()
{
    if (!d->selectedMission) return;
    dao::MissionAssignmentPtr assignment = d->missionService->missionAssignment(d->selectedMission->id());
    if (assignment.isNull()) return;

    d->missionService->cancelSync(assignment);
}
