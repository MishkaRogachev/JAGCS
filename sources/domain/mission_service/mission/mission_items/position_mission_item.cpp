#include "position_mission_item.h"

using namespace domain;

PositionMissionItem::PositionMissionItem(Mission* mission, Command command,
                                         bool relativeAltitude):
    AltitudeMissionItem(mission, command, relativeAltitude),
    m_latitude(qQNaN()),
    m_longitude(qQNaN())
{}

double PositionMissionItem::latitude() const
{
    return m_latitude;
}

double PositionMissionItem::longitude() const
{
    return m_longitude;
}

void PositionMissionItem::clone(MissionItem* mission)
{
    auto positionItem = qobject_cast<PositionMissionItem*>(mission);

    if (positionItem)
    {
        this->setLatitude(positionItem->latitude());
        this->setLongitude(positionItem->longitude());
    }

    AltitudeMissionItem::clone(mission);
}

void PositionMissionItem::setLatitude(double latitude)
{
    if (qFuzzyCompare(m_latitude, latitude)) return;

    m_latitude = latitude;
    emit latitudeChanged(latitude);
}

void PositionMissionItem::setLongitude(double longitude)
{
    if (qFuzzyCompare(m_longitude, longitude)) return;

    m_longitude = longitude;
    emit longitudeChanged(longitude);
}
