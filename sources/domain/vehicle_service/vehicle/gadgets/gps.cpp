#include "gps.h"

using namespace domain;

Gps::Gps(Fix fix, const QGeoCoordinate& coordinate):
    m_fix(fix),
    m_coordinate(coordinate)
{}

Gps::Fix Gps::fix() const
{
    return m_fix;
}

QGeoCoordinate Gps::coordinate() const
{
    return m_coordinate;
}

bool Gps::operator ==(const Gps& other)
{
    return m_fix == other.fix() &&
            m_coordinate == other.coordinate();
}

