#include "mission_display_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "mission_assignment.h"
#include "mission.h"
#include "command.h"

#include "service_registry.h"
#include "mission_service.h"
#include "command_service.h"

using namespace presentation;

MissionDisplayPresenter::MissionDisplayPresenter(QObject* parent):
    BasePresenter(parent),
    m_missionService(domain::ServiceRegistry::missionService()),
    m_commandService(domain::ServiceRegistry::commandService())
{
    connect(m_missionService, &domain::MissionService::currentItemChanged,
            [this](int vehicleId, const dao::MissionItemPtr& item) {
        if (m_assignment && m_assignment->vehicleId() == vehicleId)
            this->setViewProperty(PROPERTY(current), item->sequence());
    });
    connect(m_missionService, &domain::MissionService::missionChanged,
            [this](const dao::MissionPtr& mission) {
        if (m_assignment && m_assignment->missionId() == mission->id())
            this->updateItems();
    });
    connect(m_commandService, &domain::CommandService::commandChanged,
            [this](const dao::CommandPtr& command) {
        if (command->type() == dao::Command::GoTo)
            this->setViewProperty(PROPERTY(status), command->status());
    });
}

void MissionDisplayPresenter::setVehicle(int vehicleId)
{
    m_assignment = m_missionService->vehicleAssignment(vehicleId);

    this->updateItems();
}

void MissionDisplayPresenter::updateItems()
{
    this->setViewProperty(PROPERTY(count), m_assignment ?
                              m_missionService->mission(m_assignment->missionId())->count() : 0);
    this->setViewProperty(PROPERTY(current), m_assignment ?
                              m_missionService->currentWaypoint(
                                  m_assignment->vehicleId())->sequence() : -1);
}

void MissionDisplayPresenter::goTo(int index)
{
    if (m_assignment.isNull()) return;

    dao::CommandPtr command = dao::CommandPtr::create();
    command->setType(dao::Command::GoTo);
    command->addArgument(index);
    m_commandService->executeCommand(m_assignment->vehicleId(), command);
}
