#include "vehicle.h"

// Qt
#include <QMap>

using namespace db;

QMap<Vehicle*, int> Vehicle::m_mavIds;

Vehicle::Vehicle():
    BaseEntity(),
    m_mavId(-1),
    m_type(Unknown)
{
    m_mavIds[this] = m_mavId;
}

Vehicle::~Vehicle()
{
    m_mavIds.remove(this);
}

int Vehicle::mavId() const
{
    return m_mavId;
}

bool Vehicle::setMavId(int mavId)
{
    if (m_mavIds.values().contains(mavId)) return false;

    m_mavId = mavId;
    m_mavIds[this] = mavId;
    return true;
}

QString Vehicle::name() const
{
    return m_name;
}

void Vehicle::setName(const QString& name)
{
    m_name = name;
}

Vehicle::Type Vehicle::type() const
{
    return m_type;
}

void Vehicle::setType(Type type)
{
    m_type = type;
}
