#include "mission_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "mission.h"

using namespace presentation;

MissionPresenter::MissionPresenter(const dao::MissionPtr& mission, QObject* parent):
    BasePresenter(parent),
    m_mission(mission)
{}

MissionPresenter::~MissionPresenter()
{}

void MissionPresenter::updateView()
{
    this->setViewProperty(PROPERTY(name), m_mission->name());
    this->setViewProperty(PROPERTY(missionVisible), settings::Provider::value(
                              settings::mission::visibility + "/" + m_mission->id()));
}

void MissionPresenter::connectView(QObject* view)
{
//    connect(view, SIGNAL(remove()), this, SLOT(onRemove()));
//    connect(view, SIGNAL(rename(QString)), this, SLOT(onRename(QString)));
//    connect(view, SIGNAL(assignVehicle(int)), this, SLOT(onAssignVehicle(int)));
    connect(view, SIGNAL(setMissionVisible(bool)), this, SLOT(onSetMissionVisible(bool)));
//    connect(view, SIGNAL(uploadMission()), this, SLOT(onUploadMission()));
//    connect(view, SIGNAL(downloadMission()), this, SLOT(onDownloadMission()));
//    connect(view, SIGNAL(cancelSyncMission()), this, SLOT(onCancelSyncMission()));

    this->updateView();
}
/*
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

void MissionPresenter::onRemove()
{
    if (d->selectedMission.isNull()) return;

    d->missionService->remove(d->selectedMission);
    d->selectedMission.clear();
    this->setViewProperty(PROPERTY(selectedMission), 0);
}

void MissionPresenter::onRename(const QString& name)
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
*/
void MissionPresenter::onSetMissionVisible(bool visible)
{
    settings::Provider::setValue(settings::mission::visibility + "/" + m_mission->id(), visible);
    this->setViewProperty(PROPERTY(missionVisible), visible);
}
/*
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
*/
