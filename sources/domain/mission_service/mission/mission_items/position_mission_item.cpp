#include "position_mission_item.h"

using namespace domain;

PositionMissionItem::PositionMissionItem(Mission* mission, Command command,
                                         bool relativeAltitude):
    MissionItem(mission, command),
    m_latitude(qQNaN()),
    m_longitude(qQNaN()),
    m_altitude(qQNaN()),
    m_relativeAltitude(relativeAltitude)
{}

double PositionMissionItem::latitude() const
{
    return m_latitude;
}

double PositionMissionItem::longitude() const
{
    return m_longitude;
}

float PositionMissionItem::altitude() const
{
    return m_altitude;
}

bool PositionMissionItem::isRelativeAltitude() const
{
    return m_relativeAltitude;
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

void PositionMissionItem::setAltitude(float altitude)
{
    if (qFuzzyCompare(m_altitude, altitude)) return;

    m_altitude = altitude;
    emit altitudeChanged(altitude);
}

void PositionMissionItem::setRelativeAltitude(bool relativeAltitude)
{
    if (m_relativeAltitude == relativeAltitude) return;

    m_relativeAltitude = relativeAltitude;
    emit relativeAltitudeChanged(relativeAltitude);
}
