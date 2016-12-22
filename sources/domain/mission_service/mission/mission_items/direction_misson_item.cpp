#include "direction_misson_item.h"

using namespace domain;

DirectionMissonItem::DirectionMissonItem(Mission* mission, Command command,
                                         bool relativeAltitude):
    PositionMissionItem(mission, command, relativeAltitude),
    m_yaw(0)
{}

float DirectionMissonItem::yaw() const
{
    return m_yaw;
}

void DirectionMissonItem::setYaw(float yaw)
{
    if (m_yaw == yaw) return;

    m_yaw = yaw;
    emit yawChanged(yaw);
}
