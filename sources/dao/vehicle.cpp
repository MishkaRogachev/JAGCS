#include "vehicle.h"

// Qt
#include <QMap>

using namespace dao;

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

Vehicle::Type Vehicle::type() const
{
    return m_type;
}

void Vehicle::setType(Type type)
{
    m_type = type;
}

bool Vehicle::isOnline() const
{
    return m_online;
}

void Vehicle::setOnline(bool online)
{
    m_online = online;
}
