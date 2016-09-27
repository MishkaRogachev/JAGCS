#include "attitude.h"

using namespace domain;

Attitude::Attitude(float pitch, float roll, float yaw):
    m_pitch(pitch),
    m_roll(roll),
    m_yaw(yaw)
{}

float domain::Attitude::pitch() const
{
    return m_pitch;
}

float domain::Attitude::roll() const
{
    return m_roll;
}

float domain::Attitude::yaw() const
{
    return m_yaw;
}

bool Attitude::operator ==(const Attitude& other)
{
    return m_pitch == other.pitch() &&
            m_roll == other.roll() &&
            m_yaw == other.yaw();
}
