#include "loiter_mission_item.h"

using namespace domain;

LoiterMissionItem::LoiterMissionItem(Mission* mission, Command command):
    PositionMissionItem(mission, command, true),
    m_radius(0)
{}

float LoiterMissionItem::radius() const
{
    return m_radius;
}

void LoiterMissionItem::setRadius(float radius)
{
    if (qFuzzyCompare(m_radius, radius)) return;

    m_radius = radius;
    emit radiusChanged(radius);
}
