#include "vertical_profile_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "mission_service.h"
#include "mission.h"
#include "mission_item.h"

using namespace presentation;

VerticalProfilePresenter::VerticalProfilePresenter(QObject* parent):
    BasePresenter(parent),
    m_service(domain::ServiceRegistry::missionService())
{
    connect(m_service, &domain::MissionService::missionItemAdded, this, [this]
            (const dao::MissionItemPtr& missionItem){
        if (m_mission && m_mission->id() == missionItem->missionId()) this->updateMission();
    });

    connect(m_service, &domain::MissionService::missionItemRemoved, this, [this]
            (const dao::MissionItemPtr& missionItem){
        if (m_mission && m_mission->id() == missionItem->missionId()) this->updateMission();
    });

    connect(m_service, &domain::MissionService::missionItemChanged, this, [this]
            (const dao::MissionItemPtr& missionItem){
        if (m_mission && m_mission->id() == missionItem->missionId()) this->updateMission();
    });
}

void VerticalProfilePresenter::selectMission(const dao::MissionPtr& mission)
{
    if (m_mission == mission) return;

    m_mission = mission;
    if (this->view()) this->updateMission();
}

void VerticalProfilePresenter::updateMission()
{
    this->invokeViewMethod(PROPERTY(clearWaypoints));

    if (m_mission.isNull() || m_mission->count() < 1) return;

    QGeoCoordinate lastPosition;
    int distance = 0;

    for (const dao::MissionItemPtr& item: m_service->missionItems(m_mission->id()))
    {
        if (!item->isAltitudedItem()) continue;

        if (item->isPositionatedItem())
        {
            if (item->coordinate().isValid() && lastPosition.isValid())
            {
                distance += lastPosition.distanceTo(item->coordinate());
            }
            lastPosition = item->coordinate();
        }
        this->invokeViewMethod(PROPERTY(appendWaypoint), distance, item->altitude());
    }
}

void VerticalProfilePresenter::clearMission()
{
    this->invokeViewMethod(METHOD(clearWaypoints));
}

void VerticalProfilePresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->updateMission();
}
