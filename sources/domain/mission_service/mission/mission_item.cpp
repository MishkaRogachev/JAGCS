#include "mission_item.h"

// QT
#include <QDebug>

// Internal
#include "mission.h"

using namespace domain;

MissionItem::MissionItem(Command command, Mission* parent):
    QObject(parent),
    m_mission(parent),
    m_command(command),
    m_current(false)
{}

QGeoCoordinate MissionItem::coordinate() const
{
    return m_coordinate;
}

MissionItem::Command MissionItem::command() const
{
    return m_command;
}

unsigned MissionItem::sequence() const
{
    return m_mission->sequence((MissionItem*)this);
}

bool MissionItem::isCurrent() const
{
    return m_current;
}

void MissionItem::setCoordinate(const QGeoCoordinate& coordinate)
{
    if (m_coordinate == coordinate) return;

    m_coordinate = coordinate;
    emit coordinateChanged(coordinate);
}

void MissionItem::setGlobalCoordinate(double latitude, double longitude,
                                      float altitude)
{
    if (qFuzzyIsNull(latitude) && qFuzzyIsNull(longitude) &&
        qFuzzyIsNull(altitude))
    {
        this->setCoordinate(QGeoCoordinate());
    }
    else
    {
        this->setCoordinate(QGeoCoordinate(latitude, longitude, altitude));
    }
}

void MissionItem::setCoordinateRelativeAltitude(double latitude,
                                                double longitude,
                                                float altitude)
{
    QGeoCoordinate coordinate;

    if (!qFuzzyIsNull(latitude)) coordinate.setLatitude(latitude);
    if (!qFuzzyIsNull(longitude)) coordinate.setLatitude(longitude);

    uint8_t seq = this->sequence();
    if (seq > 0) coordinate.setAltitude(
                m_mission->item(seq - 1)->coordinate().altitude());
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
