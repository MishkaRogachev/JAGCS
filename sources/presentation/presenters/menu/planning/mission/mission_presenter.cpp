#include "mission_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "service_registry.h"
#include "mission_service.h"

#include "mission.h"

using namespace presentation;

MissionPresenter::MissionPresenter(const dao::MissionPtr& mission, QObject* parent):
    BasePresenter(parent),
    m_service(domain::ServiceRegistry::missionService()),
    m_mission(mission)
{}

MissionPresenter::~MissionPresenter()
{}

void MissionPresenter::updateView()
{
    this->setViewProperty(PROPERTY(name), m_mission->name());
    this->setViewProperty(PROPERTY(missionVisible), settings::Provider::value(
                              settings::mission::visibility + "/" + m_mission->id()));

    this->setViewProperty(PROPERTY(changed), false);
}

void MissionPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(setMissionVisible(bool)), this, SLOT(onSetMissionVisible(bool)));
//    connect(view, SIGNAL(uploadMission()), this, SLOT(onUploadMission()));
//    connect(view, SIGNAL(downloadMission()), this, SLOT(onDownloadMission()));
//    connect(view, SIGNAL(cancelSyncMission()), this, SLOT(onCancelSyncMission()));
    connect(view, SIGNAL(restore()), this, SLOT(updateView()));
    connect(view, SIGNAL(save()), this, SLOT(onSave()));
    connect(view, SIGNAL(remove()), this, SLOT(onRemove()));

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
*/
void MissionPresenter::onSetMissionVisible(bool visible)
{
    settings::Provider::setValue(settings::mission::visibility + "/" + m_mission->id(), visible);
    this->setViewProperty(PROPERTY(missionVisible), visible);

    m_service->missionChanged(m_mission);
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

void MissionPresenter::onSave()
{
    m_mission->setName(this->viewProperty(PROPERTY(name)).toString());

    if (m_service->save(m_mission)) this->setViewProperty(PROPERTY(changed), false);
}

void MissionPresenter::onRemove()
{
    m_service->remove(m_mission);
}
