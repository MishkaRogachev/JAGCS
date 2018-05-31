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
        if (m_mission == mission) this->updateMission();
    });
}

void MissionPresenter::setMission(int id)
{
    m_mission = m_service->mission(id);

    if (this->view()) this->updateMission();
}

void MissionPresenter::updateMission()
{
    this->setViewProperty(PROPERTY(name), m_mission ? m_mission->name() : "");
    this->setViewProperty(PROPERTY(count), m_mission ? m_mission->count() : 0);
    this->setViewProperty(PROPERTY(missionVisible),
                          m_mission ? settings::Provider::value(
                                          settings::mission::mission + QString::number(
                                          m_mission->id()) + "/" + settings::visibility) : false);
}

void MissionPresenter::rename(const QString& name)
{
    if (m_mission.isNull()) return;

    if (name.length() > 0) // TODO: name validator
    {
        m_mission->setName(name);
        m_service->save(m_mission);
    }
    else
    {
        this->setViewProperty(PROPERTY(name), m_mission->name());
    }
}

void MissionPresenter::remove()
{
    if (m_mission) m_service->remove(m_mission);
}

void MissionPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->updateMission();
}

void MissionPresenter::setMissionVisible(bool visible)
{
    if (m_mission.isNull()) return;

    settings::Provider::setValue(settings::mission::mission + QString::number(
                                     m_mission->id()) + "/" + settings::visibility, visible);
    this->setViewProperty(PROPERTY(missionVisible), visible);

    m_service->missionChanged(m_service->mission(m_mission->id()));
}
