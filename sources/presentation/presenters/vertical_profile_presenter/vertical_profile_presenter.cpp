#include "vertical_profile_presenter.h"

// Qt
#include <QGeoCoordinate>
#include <QVariant>
#include <QDebug>

// Internal
#include "mission_service.h"
#include "mission.h"
#include "mission_item.h"

using namespace presentation;

VerticalProfilePresenter::VerticalProfilePresenter(domain::MissionService* service,
                                                   QObject* parent):
    BasePresenter(parent),
    m_service(service)
{
    connect(service, &domain::MissionService::missionItemAdded, this, [this]
            (const dao::MissionItemPtr& missionItem){
        if (m_mission && m_mission->id() == missionItem->missionId()) this->updateMission();
    });

    connect(service, &domain::MissionService::missionItemRemoved, this, [this]
            (const dao::MissionItemPtr& missionItem){
        if (m_mission && m_mission->id() == missionItem->missionId()) this->updateMission();
    });

    connect(service, &domain::MissionService::missionItemChanged, this, [this]
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
        // TODO: another commands
        if (item->command() == dao::MissionItem::Takeoff ||
            item->command() == dao::MissionItem::Waypoint ||
            item->command() == dao::MissionItem::Landing)
        {
            QGeoCoordinate coordinate(item->latitude(), item->longitude());
            if (lastCoordinate.isValid() && coordinate.isValid())
            {
                distance += lastCoordinate.distanceTo(coordinate);
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
