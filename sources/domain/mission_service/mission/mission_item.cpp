#include "mission_item.h"

// QT
#include <QDebug>

// Internal
#include "mission.h"

using namespace domain;

MissionItem::MissionItem(Command command, Mission* mission):
    QObject(mission),
    m_mission(mission),
    m_latitude(qQNaN()),
    m_longitude(qQNaN()),
    m_altitude(command == Takeoff ? qQNaN() : 0),
    m_relativeAltitude(command != Takeoff && command != Landing),
    m_command(command),
    m_current(false)
{}

Mission* MissionItem::mission() const
{
    return m_mission;
}

unsigned MissionItem::sequence() const
{
    return m_mission->sequence((MissionItem*)this);
}

double MissionItem::latitude() const
{
    return m_latitude;
}

double MissionItem::longitude() const
{
    return m_longitude;
}

float MissionItem::altitude() const
{
    return m_altitude;
}

bool MissionItem::isRelativeAltitude() const
{
    return m_relativeAltitude;
}

MissionItem::Command MissionItem::command() const
{
    return m_command;
}

bool MissionItem::isCurrent() const
{
    return m_current;
}

void MissionItem::setLatitude(double latitude)
{
    if (qFuzzyCompare(m_latitude, latitude)) return;

    m_latitude = latitude;
    emit latitudeChanged(latitude);
}

void MissionItem::setLongitude(double longitude)
{
    if (qFuzzyCompare(m_longitude, longitude)) return;

    m_longitude = longitude;
    emit longitudeChanged(longitude);
}

void MissionItem::setAltitude(float altitude)
{
    if (qFuzzyCompare(m_altitude, altitude)) return;

    m_altitude = altitude;
    emit altitudeChanged(altitude);
}

void MissionItem::setRelativeAltitude(bool relativeAltitude)
{
    if (m_relativeAltitude == relativeAltitude) return;

    m_relativeAltitude = relativeAltitude;
    emit relativeAltitudeChanged(relativeAltitude);
}

void MissionItem::invalidatePosition()
{
    this->setLatitude(qQNaN());
    this->setLongitude(qQNaN());
}

void MissionItem::setCommand(MissionItem::Command command)
{
    if (m_command == command) return;

    m_command = command;
    emit commandChanged(command);
}

void MissionItem::setCurrent(bool current)
{
    if (m_current == current) return;

    m_current = current;
    emit currentChanged(current);
}
