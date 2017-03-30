#include "vehicle.h"

using namespace data_source;

Vehicle::Vehicle():
    BaseEntity(),
    m_mavId(0)
{}

int Vehicle::mavId() const
{
    return m_mavId;
}

void Vehicle::setMavId(int mavId)
{
    m_mavId = mavId;
}

QString Vehicle::name() const
{
    return m_name;
}

void Vehicle::setName(const QString& name)
{
    m_name = name;
}
