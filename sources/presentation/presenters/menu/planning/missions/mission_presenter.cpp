#include "mission_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "mission.h"

#include "service_registry.h"
#include "mission_service.h"

using namespace presentation;

MissionPresenter::MissionPresenter(QObject* parent):
    BasePresenter(parent),
    m_service(serviceRegistry->missionService())
{
    connect(m_service, &domain::MissionService::missionChanged, this,
            [this](const dto::MissionPtr& mission) {
        if (m_missionId == mission->id()) this->updateMission();
    });
}

void MissionPresenter::setMission(int id)
{
    m_missionId = id;

    this->updateMission();
}

void MissionPresenter::updateMission()
{
    dto::MissionPtr mission = m_service->mission(m_missionId);

    this->setViewProperty(PROPERTY(name), mission ? mission->name() : "");
    this->setViewProperty(PROPERTY(count), mission ? mission->count() : 0);
    this->setViewProperty(PROPERTY(missionVisible), settings::Provider::value(
                              settings::mission::mission + QString::number(
                                  mission->id()) + "/" + settings::mission::visibility));
}

void MissionPresenter::rename(const QString& name)
{
    dto::MissionPtr mission = m_service->mission(m_missionId);
    if (mission.isNull()) return;

    mission->setName(name);
    if (m_service->save(mission)) this->setViewProperty(PROPERTY(name), mission->name());
}

void MissionPresenter::remove()
{
    m_service->remove(m_service->mission(m_missionId));
}

void MissionPresenter::assignVehicle(int vehicleId)
{
    vehicleId ? m_service->assign(m_missionId, vehicleId) : m_service->unassign(m_missionId);
}

void MissionPresenter::setMissionVisible(bool visible)
{
    settings::Provider::setValue(settings::mission::mission + QString::number(
                                     m_missionId) + "/" + settings::mission::visibility, visible);
    this->setViewProperty(PROPERTY(missionVisible), visible);

    m_service->missionChanged(m_service->mission(m_missionId));
}
