#include "power_system.h"

using namespace domain;

PowerSystem::PowerSystem(float voltage, float current, int charge):
    m_voltage(voltage),
    m_current(current),
    m_charge(charge)
{}

float PowerSystem::voltage() const
{
    return m_voltage;
}

float PowerSystem::current() const
{
    return m_current;
}

int PowerSystem::charge() const
{
    return m_charge;
}

bool PowerSystem::operator ==(const PowerSystem& other)
{
    return qFuzzyCompare(m_voltage, other.voltage()) &&
            qFuzzyCompare(m_current, other.current()) &&
            m_charge == other.charge();
}
