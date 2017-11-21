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

void MissionPresenter::updateMission()
{
    this->setViewProperty(PROPERTY(missionId), m_mission->id());
    this->setViewProperty(PROPERTY(name), m_mission->name());
    this->setViewProperty(PROPERTY(count), m_mission->count());
    this->setViewProperty(PROPERTY(missionVisible), settings::Provider::value(
                              settings::mission::visibility + "/" + m_mission->id()));
}

void MissionPresenter::updateAssignment()
{
    dao::MissionAssignmentPtr assignment = m_service->missionAssignment(m_mission->id());
    if (assignment)
    {
        this->setViewProperty(PROPERTY(assignedVehicleId), assignment->vehicleId());
        this->setViewProperty(PROPERTY(status), assignment->status());
    }
    else
    {
        this->setViewProperty(PROPERTY(assignedVehicleId), 0);
        this->setViewProperty(PROPERTY(status), dao::MissionAssignment::NotActual);
    }
}

void MissionPresenter::rename(const QString& name)
{
    m_mission->setName(name);

    if (m_service->save(m_mission)) this->setViewProperty(PROPERTY(name), m_mission->name());
}

void MissionPresenter::remove()
{
    m_service->remove(m_mission);
}

void MissionPresenter::assignVehicle(int id)
{
    if (id)
    {
        m_service->assign(m_mission->id(), id);
    }
    else
    {
        m_service->unassign(m_mission->id());
    }
}

void MissionPresenter::setMissionVisible(bool visible)
{
    settings::Provider::setValue(settings::mission::visibility + "/" + m_mission->id(), visible);
    this->setViewProperty(PROPERTY(missionVisible), visible);

    m_service->missionChanged(m_mission);
}

void MissionPresenter::uploadMission()
{
    dao::MissionAssignmentPtr assignment = m_service->missionAssignment(m_mission->id());
    if (assignment.isNull()) return;

    m_service->upload(assignment);
}

void MissionPresenter::downloadMission()
{
    dao::MissionAssignmentPtr assignment = m_service->missionAssignment(m_mission->id());
    if (assignment.isNull()) return;

    m_service->download(assignment);
}

void MissionPresenter::cancelSyncMission()
{
    dao::MissionAssignmentPtr assignment = m_service->missionAssignment(m_mission->id());
    if (assignment.isNull()) return;

    m_service->cancelSync(assignment);
}
