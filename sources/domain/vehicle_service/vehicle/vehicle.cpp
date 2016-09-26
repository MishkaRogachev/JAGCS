#include "vehicle.h"

// Qt
#include <QDebug>

using namespace domain;

Vehicle::Vehicle(QObject* parent):
    QObject(parent),
    m_type(Vehicle::UnknownType),
    m_state(Vehicle::UnknownState)
{}

Vehicle::Type Vehicle::type() const
{
    return m_type;
}

Vehicle::State Vehicle::state() const
{
    return m_state;
}

bool Vehicle::autonomous() const
{
    return m_autonomous;
}

void Vehicle::setType(Vehicle::Type type)
{
    if (m_type == type) return;

    m_type = type;
    emit typeChanged(type);
}

void Vehicle::setState(Vehicle::State state)
{
    if (m_state == state) return;

    m_state = state;
    emit stateChanged(state);
}

void Vehicle::setAutonomous(bool autonomous)
{
    if (m_autonomous == autonomous) return;

    m_autonomous = autonomous;
    emit autonomousChanged(autonomous);
}
