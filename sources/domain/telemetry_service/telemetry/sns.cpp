#include "sns.h"

using namespace domain;

Sns::Sns(Fix fix, short satellitesVisible, const QGeoCoordinate& coordinate,
         float course, int eph, int epv):
    m_fix(fix),
    m_satellitesVisible(satellitesVisible),
    m_coordinate(coordinate),
    m_course(course),
    m_eph(eph),
    m_epv(epv)
{}

Sns::Fix Sns::fix() const
{
    return m_fix;
}

int Sns::satellitesVisible() const
{
    return m_satellitesVisible;
}

QGeoCoordinate Sns::coordinate() const
{
    return m_coordinate;
}

float Sns::altitude() const
{
    if (m_coordinate.type() != QGeoCoordinate::Coordinate3D)
        return 0;

    return m_coordinate.altitude();
}

float Sns::course() const
{
    return m_course;
}

int Sns::eph() const
{
    return m_eph;
}

int Sns::epv() const
{
    return m_epv;
}

bool Sns::operator ==(const Sns& other)
{
    return m_fix == other.fix() &&
            m_coordinate == other.coordinate() &&
            m_course == other.course() &&
            m_eph == other.eph() &&
            m_epv == other.epv();
}

