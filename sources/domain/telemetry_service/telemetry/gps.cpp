#include "gps.h"

using namespace domain;

Gps::Gps(Fix fix, short satellitesVisible, const QGeoCoordinate& coordinate,
         float course, int eph, int epv):
    m_fix(fix),
    m_satellitesVisible(satellitesVisible),
    m_coordinate(coordinate),
    m_course(course),
    m_eph(eph),
    m_epv(epv)
{}

Gps::Fix Gps::fix() const
{
    return m_fix;
}

int Gps::satellitesVisible() const
{
    return m_satellitesVisible;
}

QGeoCoordinate Gps::coordinate() const
{
    return m_coordinate;
}

float Gps::altitude() const
{
    if (m_coordinate.type() != QGeoCoordinate::Coordinate3D)
        return 0;

    return m_coordinate.altitude();
}

float Gps::course() const
{
    return m_course;
}

int Gps::eph() const
{
    return m_eph;
}

int Gps::epv() const
{
    return m_epv;
}

bool Gps::operator ==(const Gps& other)
{
    return m_fix == other.fix() &&
            m_coordinate == other.coordinate() &&
            m_course == other.course() &&
            m_eph == other.eph() &&
            m_epv == other.epv();
}

