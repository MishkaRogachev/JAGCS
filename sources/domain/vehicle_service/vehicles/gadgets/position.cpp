#include "position.h"

using namespace domain;

Position::Position(const QGeoCoordinate& coordinate,
                   const QVector3D& vector):
    m_coordinate(coordinate),
    m_vector(vector)
{}

const QGeoCoordinate& Position::coordinate() const
{
    return m_coordinate;
}

const QVector3D& Position::vector() const
{
    return m_vector;
}

bool Position::operator ==(const Position& other)
{
    return m_coordinate == other.coordinate() &&
            m_vector == vector();
}
