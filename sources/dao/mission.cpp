#include "mission.h"

// Internal
#include "mission_item.h"

using namespace dao;

QString Mission::name() const
{
    return m_name;
}

void Mission::setName(const QString& name)
{
    m_name = name;
}

int Mission::count() const
{
    return m_count;
}

void Mission::setCount(int count)
{
    m_count = count;
}

float Mission::homeAltitude() const
{
    return m_homeAltitude;
}

void Mission::setHomeAltitude(float homeAltitude)
{
    m_homeAltitude = homeAltitude;
}

