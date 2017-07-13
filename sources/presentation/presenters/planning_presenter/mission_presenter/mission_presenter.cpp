#include "mission_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "domain_entry.h"

#include "db_facade.h"
#include "mission.h"
#include "mission_item.h"
#include "mission_assignment.h"
#include "vehicle.h"

#include "command_service.h"

#include "mission_item_presenter.h"

using namespace presentation;

class MissionPresenter::Impl
{
public:
    db::DbFacade* dbFacade;
    domain::CommandService* commandService;

    db::MissionPtr selectedMission;
    db::MissionPtrList missions;

    MissionItemPresenter* item;
};

using namespace presentation;

MissionPresenter::MissionPresenter(domain::DomainEntry* entry, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->dbFacade = entry->dbFacade();
    d->commandService = entry->commandService();

    d->missions.append(d->dbFacade->missions());

    connect(d->dbFacade, &db::DbFacade::missionAdded, this, &MissionPresenter::onMissionAdded);
    connect(d->dbFacade, &db::DbFacade::missionRemoved, this, &MissionPresenter::onMissionRemoved);

    connect(d->dbFacade, &db::DbFacade::assignmentAdded, this, &MissionPresenter::updateAssignment);
    connect(d->dbFacade, &db::DbFacade::assignmentRemoved, this, &MissionPresenter::updateAssignment);
    connect(d->dbFacade, &db::DbFacade::assignmentChanged,  this, &MissionPresenter::updateAssignment);

    connect(d->dbFacade, &db::DbFacade::missionItemAdded, this, &MissionPresenter::updateStatuses);
    connect(d->dbFacade, &db::DbFacade::missionItemRemoved, this, &MissionPresenter::updateStatuses);
    connect(d->dbFacade, &db::DbFacade::missionItemChanged, this, &MissionPresenter::updateStatuses);

    connect(d->dbFacade, &db::DbFacade::vehicleAdded, this, &MissionPresenter::updateVehiclesBox);
    connect(d->dbFacade, &db::DbFacade::vehicleRemoved, this, &MissionPresenter::updateVehiclesBox);

    d->item = new MissionItemPresenter(d->dbFacade, this);
}

MissionPresenter::~MissionPresenter()
{}

void MissionPresenter::selectMission(const db::MissionPtr& mission)
{
    d->selectedMission = mission;
    d->item->setMission(d->selectedMission);

    this->setViewProperty(PROPERTY(selectedMission),
                          d->missions.indexOf(d->selectedMission) + 1);
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

void MissionPresenter::onMissionAdded(const db::MissionPtr& mission)
{
    d->missions.append(mission);
    this->updateMissionsBox();
}

void MissionPresenter::onMissionRemoved(const db::MissionPtr& mission)
{
    d->missions.removeOne(mission);
    this->updateMissionsBox();
}

void MissionPresenter::updateMissionsBox()
{
    this->setViewConnected(false);

    QStringList missions;
    missions.append(QString());

    for (const db::MissionPtr& mission: d->missions)
    {
        missions.append(mission->name());
    }
    this->setViewProperty(PROPERTY(missions), QVariant::fromValue(missions));
    this->setViewProperty(PROPERTY(selectedMission),
                          d->missions.indexOf(d->selectedMission) + 1);
    this->setViewConnected(true);
}

void MissionPresenter::updateVehiclesBox()
{
    this->setViewConnected(false);

    QStringList vehicles;
    vehicles.append(QString());

    for (const db::VehiclePtr& vehicle: d->dbFacade->vehicles())
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
        db::MissionAssignmentPtr assignment =
                d->dbFacade->missionAssignment(d->selectedMission->id());
        if (assignment)
        {
            db::VehiclePtr vehicle = d->dbFacade->vehicle(assignment->vehicleId());
            if (vehicle)
            {
                this->setViewProperty(PROPERTY(assignedVehicle),
                                      d->dbFacade->vehicles().indexOf(vehicle) + 1);
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
        for (const db::MissionItemPtr& item:
             d->dbFacade->missionItems(d->selectedMission->id()))
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
        this->selectMission(db::MissionPtr());
    }
}

void MissionPresenter::onAddMission()
{
    db::MissionPtr mission = db::MissionPtr::create();

    mission->setName(tr("New Mission %1").arg(d->dbFacade->missions().count()));

    d->dbFacade->save(mission);
    this->selectMission(mission);
}

void MissionPresenter::onAddItem()
{
    if (d->selectedMission.isNull()) return;

    d->dbFacade->addNewMissionItem(d->selectedMission->id());
    d->item->selectItem(d->selectedMission->count());
}

void MissionPresenter::onRemoveMission()
{
    if (d->selectedMission.isNull()) return;

    d->dbFacade->remove(d->selectedMission);
    d->selectedMission.clear();
    this->setViewProperty(PROPERTY(selectedMission), 0);

    d->item->setMission(db::MissionPtr());
}

void MissionPresenter::onRenameMission(const QString& name)
{
    if (d->selectedMission.isNull() || name.isEmpty()) return;

    // TODO: check unique name
    d->selectedMission->setName(name);
    d->dbFacade->save(d->selectedMission);
    this->updateMissionsBox();
}

void MissionPresenter::onAssignVehicle(int index)
{
    // TODO: fix vehicle assignment
    if (!d->selectedMission) return;

    db::VehiclePtrList vehicles = d->dbFacade->vehicles();
    db::VehiclePtr vehicle = (index > 0 && index <= vehicles.count()) ?
                                 vehicles.at(index - 1) : db::VehiclePtr();

    if (vehicle)
    {
        d->dbFacade->assign(d->selectedMission->id(), vehicle->id());
    }
    else
    {
        d->dbFacade->unassign(d->selectedMission->id());
    }
}

void MissionPresenter::onUploadMission()
{
    if (!d->selectedMission) return;
    db::MissionAssignmentPtr assignment = d->dbFacade->missionAssignment(d->selectedMission->id());
    if (assignment.isNull()) return;

    d->commandService->upload(assignment);
}

void MissionPresenter::onDownloadMission()
{
    if (!d->selectedMission) return;
    db::MissionAssignmentPtr assignment = d->dbFacade->missionAssignment(d->selectedMission->id());
    if (assignment.isNull()) return;

    d->commandService->download(assignment);
}
