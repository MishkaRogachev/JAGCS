#include "mission_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "domain_facade.h"

#include "mission_service.h"
#include "vehicle_service.h"

#include "mission.h"
#include "mission_assignment.h"
#include "vehicle_description.h"

using namespace presentation;

class MissionPresenter::Impl
{
public:
    domain::MissionService* missionService;
    domain::VehicleService* vehicleService;

    db::MissionPtr selectedMission;
};

using namespace presentation;

MissionPresenter::MissionPresenter(domain::DomainFacade* facade,
                                   QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->missionService = facade->missionService();
    d->vehicleService = facade->vehicleService();

    connect(d->missionService, &domain::MissionService::missionAdded,
            this, &MissionPresenter::updateMissions);
    connect(d->missionService, &domain::MissionService::missionRemoved,
            this, &MissionPresenter::updateMissions);

    connect(d->vehicleService, &domain::VehicleService::vehicleAdded,
            this, &MissionPresenter::updateVehicles);
    connect(d->vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &MissionPresenter::updateVehicles);
}

MissionPresenter::~MissionPresenter()
{}

void MissionPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->updateVehicles();
    this->updateMissions();
}

void MissionPresenter::setViewConnected(bool connected)
{
    if (connected)
    {
        connect(this->view(), SIGNAL(selectMission(QString)),
                this, SLOT(onSelectMission(QString)));
        connect(this->view(), SIGNAL(addMission()),
                this, SLOT(onAddMission()));
        connect(this->view(), SIGNAL(removeMission()),
                this, SLOT(onRemoveMission()));
        connect(this->view(), SIGNAL(renameMission(QString)),
                this, SLOT(onRenameMission(QString)));
        connect(this->view(), SIGNAL(assignVehicle(QString)),
                this, SLOT(onAssignVehicle(QString)));
    }
    else
    {
        disconnect(this->view(), 0, this, 0);
    }
}

void MissionPresenter::updateMissions()
{
    this->setViewConnected(false);

    QStringList missions;
    missions.append(QString());

    for (const db::MissionPtr& mission: d->missionService->missions())
    {
        missions.append(mission->name());
    }
    this->setViewProperty(PROPERTY(missions), QVariant::fromValue(missions));
    this->setViewProperty(PROPERTY(selectedMission), d->selectedMission.isNull() ?
                              QString() : d->selectedMission->name());
    this->setViewConnected(true);

    this->updateAssignment();
}

void MissionPresenter::updateAssignment()
{
    this->setViewConnected(false);
    if (d->selectedMission)
    {
        db::MissionAssignmentPtr assignment = d->missionService->assignment(
                                                  d->selectedMission);
        if (assignment)
        {
            db::VehicleDescriptionPtr vehicle =
                    d->vehicleService->description(assignment->vehicleId());

            this->setViewProperty(PROPERTY(assignedVehicle), vehicle->name());
            this->setViewConnected(true);
            return;
        }
    }
    this->setViewProperty(PROPERTY(assignedVehicle), QString());
    this->setViewConnected(true);
}

void MissionPresenter::updateVehicles()
{
    this->setViewConnected(false);

    QStringList vehicles;
    vehicles.append(QString());

    for (const db::VehicleDescriptionPtr& vehicle: d->vehicleService->descriptions())
    {
        vehicles.append(vehicle->name());
    }
    this->setViewProperty(PROPERTY(vehicles), QVariant::fromValue(vehicles));
    this->setViewConnected(true);

    this->updateAssignment();
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
    this->updateAssignment();
}

void MissionPresenter::onAddMission()
{
    db::MissionPtr mission = db::MissionPtr::create();

    mission->setName(tr("New Mission %1").arg(
                         d->missionService->missions().count()));

    d->missionService->saveMission(mission);
    this->setViewProperty(PROPERTY(selectedMission), mission->name());
}

void MissionPresenter::onRemoveMission()
{
    if (d->selectedMission.isNull()) return;

    d->missionService->removeMission(d->selectedMission);
    this->setViewProperty(PROPERTY(selectedMission), QString());
}

void MissionPresenter::onRenameMission(const QString& name)
{
    if (d->selectedMission.isNull()) return;

    d->selectedMission->setName(name);
    d->missionService->saveMission(d->selectedMission);
    this->updateMissions();
    this->setViewProperty(PROPERTY(selectedMission), name);
}

void MissionPresenter::onAssignVehicle(const QString& name)
{
    if (!d->selectedMission) return;
    db::VehicleDescriptionPtr vehicle =
            d->vehicleService->findDescriptiontByName(name);

    if (vehicle)
    {
        d->missionService->assign(d->selectedMission, vehicle);
    }
    else
    {
        d->missionService->unassign(d->selectedMission);
    }

    this->updateAssignment();
}
