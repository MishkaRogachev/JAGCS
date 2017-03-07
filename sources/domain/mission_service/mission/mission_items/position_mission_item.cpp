#include "position_mission_item.h"

// Qt
#include <QGeoCoordinate>
#include <QDebug>

// Internal
#include "mission.h"

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

float PositionMissionItem::azimuth() const
{
    QGeoCoordinate endPoint(m_latitude, m_longitude);
    if (this->sequence() < 1 || !endPoint.isValid()) return 0.0;

    PositionMissionItem* previous = nullptr;
    for (uint8_t seq = this->sequence() - 1; seq >= 0 ; seq--)
    {
        previous = qobject_cast<PositionMissionItem*>(
                       this->mission()->item(seq));
        if (!previous) continue;

        QGeoCoordinate startPoint(previous->latitude(), previous->longitude());
        if (!startPoint.isValid()) return 0.0;

        return startPoint.azimuthTo(endPoint);
    }
    return 0.0;
}

void PositionMissionItem::clone(AbstractMissionItem* mission)
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
    emit dataChanged();
}

void PositionMissionItem::setLongitude(double longitude)
{
    if (qFuzzyCompare(m_longitude, longitude)) return;

    m_longitude = longitude;
    emit longitudeChanged(longitude);
    emit dataChanged();
}
