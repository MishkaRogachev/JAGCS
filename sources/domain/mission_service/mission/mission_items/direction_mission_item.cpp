#include "direction_mission_item.h"

using namespace domain;

DirectionMissionItem::DirectionMissionItem(Mission* mission, Command command,
                                         bool relativeAltitude):
    PositionMissionItem(mission, command, relativeAltitude),
    m_yaw(0)
{}

float DirectionMissionItem::yaw() const
{
    return m_yaw;
}

void DirectionMissionItem::clone(MissionItem* mission)
{
    auto directionItem = qobject_cast<DirectionMissionItem*>(mission);

    if (directionItem)
    {
        this->setYaw(directionItem->yaw());
    }

    MissionItem::clone(mission);
}

void DirectionMissionItem::setYaw(float yaw)
{
    if (m_yaw == yaw) return;

    m_yaw = yaw;
    emit yawChanged(yaw);
}
