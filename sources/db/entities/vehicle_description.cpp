#include "vehicle_description.h"

// Qt
#include <QMap>

using namespace db;

QMap<VehicleDescription*, int> VehicleDescription::m_mavIds;

VehicleDescription::VehicleDescription():
    BaseEntity(),
    m_mavId(-1)
{
    m_mavIds[this] = m_mavId;
}

VehicleDescription::~VehicleDescription()
{
    m_mavIds.remove(this);
}

int VehicleDescription::mavId() const
{
    return m_mavId;
}

bool VehicleDescription::setMavId(int mavId)
{
    if (m_mavIds.values().contains(mavId)) return false;

    m_mavId = mavId;
    m_mavIds[this] = mavId;
    return true;
}

QString VehicleDescription::name() const
{
    return m_name;
}

void VehicleDescription::setName(const QString& name)
{
    m_name = name;
}
