#include "vehicle_description.h"

using namespace data_source;

VehicleDescription::VehicleDescription():
    BaseEntity(),
    m_mavId(0)
{}

int VehicleDescription::mavId() const
{
    return m_mavId;
}

void VehicleDescription::setMavId(int mavId)
{
    m_mavId = mavId;
}

QString VehicleDescription::name() const
{
    return m_name;
}

void VehicleDescription::setName(const QString& name)
{
    m_name = name;
}
