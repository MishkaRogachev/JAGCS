#include "mission_assignment_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "mission_assignment.h"

#include "service_registry.h"
#include "mission_service.h"

using namespace presentation;

MissionAssignmentPresenter::MissionAssignmentPresenter(QObject* parent):
    BasePresenter(parent),
    m_service(serviceRegistry->missionService()),
    m_missionId(0)
{
    connect(m_service, &domain::MissionService::assignmentAdded, this,
            [this](const dto::MissionAssignmentPtr& assignment) {
        if (m_missionId == assignment->missionId()) this->updateAssignment();
    });
    connect(m_service, &domain::MissionService::assignmentRemoved, this,
            [this](const dto::MissionAssignmentPtr& assignment) {
        if (m_missionId == assignment->missionId()) this->updateAssignment();
    });
    connect(m_service, &domain::MissionService::assignmentChanged, this,
            [this](const dto::MissionAssignmentPtr& assignment) {
        if (m_missionId == assignment->missionId()) this->updateAssignment();
    });
}

void MissionAssignmentPresenter::setMission(int id)
{
    m_missionId = id;

    if (this->view()) this->updateAssignment();
}

void MissionAssignmentPresenter::updateAssignment()
{
    dto::MissionAssignmentPtr assignment =  m_service->missionAssignment(m_missionId);

    if (assignment)
    {
        this->setViewProperty(PROPERTY(assignedVehicleId), assignment->vehicleId());
        this->setViewProperty(PROPERTY(status), assignment->status());
        this->setViewProperty(PROPERTY(progress), assignment->progress());
    }
    else
    {
        this->setViewProperty(PROPERTY(assignedVehicleId), 0);
        this->setViewProperty(PROPERTY(status), dto::MissionAssignment::NotActual);
        this->setViewProperty(PROPERTY(progress), 0);
    }
}

void MissionAssignmentPresenter::assignVehicle(int vehicleId)
{
    vehicleId ? m_service->assign(m_missionId, vehicleId) : m_service->unassign(m_missionId);
}


void MissionAssignmentPresenter::uploadMission()
{
    dto::MissionAssignmentPtr assignment = m_service->missionAssignment(m_missionId);
    if (assignment.isNull()) return;

    m_service->upload(assignment);
}

void MissionAssignmentPresenter::downloadMission()
{
    dto::MissionAssignmentPtr assignment = m_service->missionAssignment(m_missionId);
    if (assignment.isNull()) return;

    m_service->download(assignment);
}

void MissionAssignmentPresenter::cancelSyncMission()
{
    dto::MissionAssignmentPtr assignment = m_service->missionAssignment(m_missionId);
    if (assignment.isNull()) return;

    m_service->cancelSync(assignment);
}

void MissionAssignmentPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->updateAssignment();
}
