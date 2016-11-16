#include "gps.h"

using namespace domain;

Gps::Gps(Fix fix, short satellitesVisible, const QGeoCoordinate& coordinate,
         int eph, int epv):
    m_fix(fix),
    m_satellitesVisible(satellitesVisible),
    m_coordinate(coordinate),
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
            m_coordinate == other.coordinate();
}

