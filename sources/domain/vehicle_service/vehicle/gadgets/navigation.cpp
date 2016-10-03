#include "navigation.h"

using namespace domain;

Navigation::Navigation(const QGeoCoordinate& position,
                       const QVector3D& groundSpeed):
    m_position(position),
    m_groundSpeed(groundSpeed)
{}

QGeoCoordinate Navigation::position() const
{
    return m_position;
}

QVector3D Navigation::groundSpeed() const
{
    return m_groundSpeed;
}
