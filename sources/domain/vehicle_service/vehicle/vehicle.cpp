#include "vehicle.h"

using namespace domain;

Vehicle::Vehicle(QObject* parent):
    QObject(parent)
{}

Vehicle::Type Vehicle::type() const
{
    return m_type;
}

void Vehicle::setType(Vehicle::Type type)
{
    if (m_type == type) return;

    m_type = type;
    emit typeChanged(type);
}
