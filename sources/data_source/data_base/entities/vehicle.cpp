#include "vehicle.h"

using namespace data_source;

Vehicle::Vehicle(int id):
    BaseEntity(id),
    m_mavId(0)
{}

QString Vehicle::tableName()
{
    return "vehicles";
}

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
