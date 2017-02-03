#include "wind.h"

using namespace domain;

Wind::Wind(float direction, float speed, float verticalSpeed):
    m_direction(direction),
    m_speed(speed),
    m_verticalSpeed(verticalSpeed)
{}

float Wind::direction() const
{
    return m_direction;
}

float Wind::speed() const
{
    return m_speed;
}

float Wind::verticalSpeed() const
{
    return m_verticalSpeed;
}

bool Wind::operator ==(const Wind& other)
{
    return qFuzzyCompare(m_direction, other.direction()) &&
           qFuzzyCompare(m_speed, other.speed()) &&
           qFuzzyCompare(m_verticalSpeed, other.verticalSpeed());
}
