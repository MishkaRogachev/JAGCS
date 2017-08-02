#include "vertical_profile_presenter.h"

// Qt
#include <QGeoCoordinate>
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

    if (m_mission.isNull()) return;
    QGeoCoordinate lastCoordinate;
    int distance = 0;
    for (const dao::MissionItemPtr& item: m_service->missionItems(m_mission->id()))
    {
        // TODO: has altitude
        if (item->command() == dao::MissionItem::Home ||
            item->command() == dao::MissionItem::Waypoint ||
            item->command() == dao::MissionItem::Takeoff ||
            item->command() == dao::MissionItem::Landing ||
            item->command() == dao::MissionItem::LoiterUnlim ||
            item->command() == dao::MissionItem::LoiterAltitude ||
            item->command() == dao::MissionItem::LoiterTurns ||
            item->command() == dao::MissionItem::LoiterTime)
        {
            QGeoCoordinate coordinate(item->latitude(), item->longitude());
            if (lastCoordinate.isValid() && coordinate.isValid())
            {
                distance += lastCoordinate.distanceTo(coordinate);
                // TODO: fix distance for loiters, continue
            }
            lastCoordinate = coordinate;
        }

        // TODO: relative altitude
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
