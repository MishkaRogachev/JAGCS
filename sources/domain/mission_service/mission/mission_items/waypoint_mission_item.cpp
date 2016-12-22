#include "waypoint_mission_item.h"

using namespace domain;

WaypointMissionItem::WaypointMissionItem(Mission* mission):
    PositionMissionItem(mission, Waypoint),
    m_acceptanceRadius(0)
{}

float WaypointMissionItem::acceptanceRadius() const
{
    return m_acceptanceRadius;
}

void WaypointMissionItem::setAcceptanceRadius(float acceptanceRadius)
{
    if (m_acceptanceRadius == acceptanceRadius) return;

    m_acceptanceRadius = acceptanceRadius;
    emit acceptanceRadiusChanged(acceptanceRadius);
}
