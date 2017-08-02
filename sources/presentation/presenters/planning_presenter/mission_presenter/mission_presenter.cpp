#include "mission_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "service_registry.h"

#include "mission_service.h"
#include "mission.h"
#include "mission_item.h"
#include "mission_assignment.h"

#include "vehicle_service.h"
#include "vehicle.h"

#include "command_service.h"

#include "mission_item_presenter.h"

using namespace presentation;

class MissionPresenter::Impl
{
public:
    domain::VehicleService* vehicleService;
    domain::MissionService* missionService;

    dao::MissionPtr selectedMission;
    dao::MissionPtrList missions;

    MissionItemPresenter* item;
};

using namespace presentation;

MissionPresenter::MissionPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->vehicleService = domain::ServiceRegistry::vehicleService();
    d->missionService = domain::ServiceRegistry::missionService();

    d->missions.append(d->missionService->missions());

    connect(d->missionService, &domain::MissionService::missionAdded,
            this, &MissionPresenter::onMissionAdded);
    connect(d->missionService, &domain::MissionService::missionRemoved,
            this, &MissionPresenter::onMissionRemoved);

    connect(d->missionService, &domain::MissionService::assignmentAdded,
            this, &MissionPresenter::updateAssignment);
    connect(d->missionService, &domain::MissionService::assignmentRemoved,
            this, &MissionPresenter::updateAssignment);
    connect(d->missionService, &domain::MissionService::assignmentChanged,
            this, &MissionPresenter::updateAssignment);

    connect(d->missionService, &domain::MissionService::missionItemAdded,
            this, &MissionPresenter::updateStatuses);
    connect(d->missionService, &domain::MissionService::missionItemRemoved,
            this, &MissionPresenter::updateStatuses);
    connect(d->missionService, &domain::MissionService::missionItemChanged,
            this, &MissionPresenter::updateStatuses);

    connect(d->vehicleService, &domain::VehicleService::vehicleAdded,
            this, &MissionPresenter::updateVehiclesBox);
    connect(d->vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &MissionPresenter::updateVehiclesBox);

    d->item = new MissionItemPresenter(d->missionService, this);
}

MissionPresenter::~MissionPresenter()
{}

void MissionPresenter::selectMission(const dao::MissionPtr& mission)
{
    d->selectedMission = mission;
    d->item->setMission(d->selectedMission);

    this->setViewProperty(PROPERTY(selectedMission), d->missions.indexOf(d->selectedMission) + 1);
    this->updateAssignment();
    this->updateStatuses();

    emit missionSelected(mission);
}

void MissionPresenter::connectView(QObject* view)
{
    d->item->setView(view->findChild<QObject*>(NAME(missionItem)));

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
        connect(this->view(), SIGNAL(uploadMission()), this, SLOT(onUploadMission()));
        connect(this->view(), SIGNAL(downloadMission()), this, SLOT(onDownloadMission()));
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
            this->setViewConnected(true);
            return;
        }
    }
    this->setViewProperty(PROPERTY(assignedVehicle), 0);

    this->setViewConnected(true);
}

void MissionPresenter::updateStatuses()
{
    QStringList statuses;

    if (d->selectedMission)
    {
        for (const dao::MissionItemPtr& item:
             d->missionService->missionItems(d->selectedMission->id()))
        {
            statuses.append(QString::number(item->status()));
        }
    }

    this->setViewProperty(PROPERTY(statuses), statuses);
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
    d->item->selectItem(d->selectedMission->count() - 1);
    d->item->setPicking(true); // TODO: check coordinate usefull
}

void MissionPresenter::onRemoveMission()
{
    if (d->selectedMission.isNull()) return;

    d->missionService->remove(d->selectedMission);
    d->selectedMission.clear();
    this->setViewProperty(PROPERTY(selectedMission), 0);

    d->item->setMission(dao::MissionPtr());
}

void MissionPresenter::onRenameMission(const QString& name)
{
    if (d->selectedMission.isNull() || name.isEmpty()) return;

    // TODO: check unique name
    d->selectedMission->setName(name);
    d->missionService->save(d->selectedMission);
    this->updateMissionsBox();
}

void MissionPresenter::onAssignVehicle(int index)
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
