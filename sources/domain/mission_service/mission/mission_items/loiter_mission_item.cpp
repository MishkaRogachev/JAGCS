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

void LoiterMissionItem::clone(MissionItem* mission)
{
    auto loiterItem = qobject_cast<LoiterMissionItem*>(mission);

    if (loiterItem)
    {
        this->setRadius(loiterItem->radius());
    }

    PositionMissionItem::clone(mission);
}

void LoiterMissionItem::setRadius(float radius)
{
    if (qFuzzyCompare(m_radius, radius)) return;

    m_radius = radius;
    emit radiusChanged(radius);
}
