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

MissionPresenter::MissionPresenter(QObject* parent):
    BasePresenter(parent),
    m_service(domain::ServiceRegistry::missionService())
{
    connect(m_service, &domain::MissionService::missionChanged, this,
            [this](const dao::MissionPtr& mission) {
        if (m_mission && m_mission == mission) this->updateMission();
    });

    connect(m_service, &domain::MissionService::assignmentAdded, this,
            [this](const dao::MissionAssignmentPtr& assignment) {
        if (m_mission && m_mission->id() == assignment->missionId()) this->updateAssignment();
    });

    connect(m_service, &domain::MissionService::assignmentRemoved, this,
            [this](const dao::MissionAssignmentPtr& assignment) {
        if (m_mission && m_mission->id() == assignment->missionId()) this->updateAssignment();
    });

    connect(m_service, &domain::MissionService::assignmentChanged, this,
            [this](const dao::MissionAssignmentPtr& assignment) {
        if (m_mission && m_mission->id() == assignment->missionId()) this->updateAssignment();
    });
}

void MissionPresenter::setMission(int id)
{
    m_mission = m_service->mission(id);

    this->updateMission();
    this->updateAssignment();
}

void MissionPresenter::updateMission()
{
    if (m_mission.isNull()) return;

    this->setViewProperty(PROPERTY(name), m_mission ? m_mission->name() : "");
    this->setViewProperty(PROPERTY(count), m_mission ? m_mission->count() : 0);
    this->setViewProperty(PROPERTY(missionVisible), m_mission ?
                              settings::Provider::value(
                                  settings::mission::visibility + "/" +
                                  QString::number(m_mission->id())) : false);
}

void MissionPresenter::updateAssignment()
{
    dao::MissionAssignmentPtr assignment = m_mission ?
                                               m_service->missionAssignment(m_mission->id()) :
                                               dao::MissionAssignmentPtr();
    if (assignment)
    {
        this->setViewProperty(PROPERTY(assignedVehicleId), assignment->vehicleId());
        this->setViewProperty(PROPERTY(status), assignment->status());
        this->setViewProperty(PROPERTY(progress), assignment->progress());
    }
    else
    {
        this->setViewProperty(PROPERTY(assignedVehicleId), 0);
        this->setViewProperty(PROPERTY(status), dao::MissionAssignment::NotActual);
        this->setViewProperty(PROPERTY(progress), 0);
    }
}

void MissionPresenter::rename(const QString& name)
{
    if (m_mission.isNull()) return;

    m_mission->setName(name);
    if (m_service->save(m_mission)) this->setViewProperty(PROPERTY(name), m_mission->name());
}

void MissionPresenter::remove()
{
    if (m_mission) m_service->remove(m_mission);
}

void MissionPresenter::assignVehicle(int id)
{
    if (m_mission.isNull()) return;

    id ? m_service->assign(m_mission->id(), id) : m_service->unassign(m_mission->id());
}

void MissionPresenter::setMissionVisible(bool visible)
{
    if (m_mission.isNull()) return;

    settings::Provider::setValue(settings::mission::visibility + "/" +
                                 QString::number(m_mission->id()), visible);
    this->setViewProperty(PROPERTY(missionVisible), visible);

    m_service->missionChanged(m_mission);
}

void MissionPresenter::uploadMission()
{
    if (m_mission.isNull()) return;

    dao::MissionAssignmentPtr assignment = m_service->missionAssignment(m_mission->id());
    if (assignment.isNull()) return;

    m_service->upload(assignment);
}

void MissionPresenter::downloadMission()
{
    if (m_mission.isNull()) return;

    dao::MissionAssignmentPtr assignment = m_service->missionAssignment(m_mission->id());
    if (assignment.isNull()) return;

    m_service->download(assignment);
}

void MissionPresenter::cancelSyncMission()
{
    if (m_mission.isNull()) return;

    dao::MissionAssignmentPtr assignment = m_service->missionAssignment(m_mission->id());
    if (assignment.isNull()) return;

    m_service->cancelSync(assignment);
}
