#include "sns.h"

using namespace domain;

Sns::Sns(Fix fix, short satellitesVisible, const QGeoCoordinate& coordinate,
         float course, float groundSpeed, int eph, int epv, quint64 time):
    m_fix(fix),
    m_satellitesVisible(satellitesVisible),
    m_coordinate(coordinate),
    m_course(course),
    m_groundSpeed(groundSpeed),
    m_eph(eph),
    m_epv(epv),
    m_time(time)
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
    if (m_coordinate.type() != QGeoCoordinate::Coordinate3D) return 0;

    return m_coordinate.altitude();
}

float Sns::course() const
{
    return m_course;
}

float Sns::groundSpeed() const
{
    return m_groundSpeed;
}

int Sns::eph() const
{
    return m_eph;
}

int Sns::epv() const
{
    return m_epv;
}

quint64 Sns::time() const
{
    return m_time;
}

bool Sns::operator ==(const Sns& other)
{
    return m_fix == other.fix() &&
            m_coordinate == other.coordinate() &&
            m_course == other.course() &&
            m_groundSpeed == other.groundSpeed() &&
            m_eph == other.eph() &&
            m_epv == other.epv() &&
            m_time == other.time();
}
