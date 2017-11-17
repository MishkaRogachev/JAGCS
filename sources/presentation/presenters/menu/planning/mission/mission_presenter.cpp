#include "mission_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "mission.h"
#include "mission_assignment.h"

#include "service_registry.h"
#include "mission_service.h"

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

    dao::MissionAssignmentPtr assignment = m_service->missionAssignment(m_mission->id());
    if (assignment)
    {/*
        dao::VehiclePtr vehicle = d->vehicleService->vehicle(assignment->vehicleId());
        if (vehicle)
        {
            this->setViewProperty(PROPERTY(assignedVehicle),
                                  d->vehicleService->vehicles().indexOf(vehicle) + 1);
        }

        this->setViewProperty(PROPERTY(status), assignment->status());
        this->setViewConnected(true);
        */
    }
    else
    {
        this->setViewProperty(PROPERTY(assignedVehicle), 0);
        this->setViewProperty(PROPERTY(status), dao::MissionAssignment::NotActual);
    }

    this->setViewProperty(PROPERTY(changed), false);
}

void MissionPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(rename(QString)), this, SLOT(onRename(QString)));
    connect(view, SIGNAL(remove()), this, SLOT(onRemove()));
    connect(view, SIGNAL(setMissionVisible(bool)), this, SLOT(onSetMissionVisible(bool)));
    connect(view, SIGNAL(uploadMission()), this, SLOT(onUploadMission()));
    connect(view, SIGNAL(downloadMission()), this, SLOT(onDownloadMission()));
    connect(view, SIGNAL(cancelSyncMission()), this, SLOT(onCancelSyncMission()));

    this->updateView();
}

void MissionPresenter::onRename(const QString& name)
{
    m_mission->setName(name);

    if (m_service->save(m_mission)) this->setViewProperty(PROPERTY(name), m_mission->name());
}

void MissionPresenter::onRemove()
{
    m_service->remove(m_mission);
}


void MissionPresenter::onSetMissionVisible(bool visible)
{
    settings::Provider::setValue(settings::mission::visibility + "/" + m_mission->id(), visible);
    this->setViewProperty(PROPERTY(missionVisible), visible);

    m_service->missionChanged(m_mission);
}

void MissionPresenter::onUploadMission()
{
    dao::MissionAssignmentPtr assignment = m_service->missionAssignment(m_mission->id());
    if (assignment.isNull()) return;

    m_service->upload(assignment);
}

void MissionPresenter::onDownloadMission()
{
    dao::MissionAssignmentPtr assignment = m_service->missionAssignment(m_mission->id());
    if (assignment.isNull()) return;

    m_service->download(assignment);
}

void MissionPresenter::onCancelSyncMission()
{
    dao::MissionAssignmentPtr assignment = m_service->missionAssignment(m_mission->id());
    if (assignment.isNull()) return;

    m_service->cancelSync(assignment);
}
