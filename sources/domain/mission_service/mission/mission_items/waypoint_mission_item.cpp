#include "waypoint_mission_item.h"

using namespace domain;

WaypointMissionItem::WaypointMissionItem(Mission* mission, float acceptanceRadius):
    PositionMissionItem(mission, Command::Waypoint, true),
    m_acceptanceRadius(acceptanceRadius)
{}

float WaypointMissionItem::acceptanceRadius() const
{
    return m_acceptanceRadius;
}

void WaypointMissionItem::setAcceptanceRadius(float acceptanceRadius)
{
    if (qFuzzyCompare(m_acceptanceRadius, acceptanceRadius)) return;

    m_acceptanceRadius = acceptanceRadius;
    emit acceptanceRadiusChanged(acceptanceRadius);
}
