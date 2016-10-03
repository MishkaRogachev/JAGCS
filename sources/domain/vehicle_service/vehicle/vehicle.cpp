#include "vehicle.h"

// Qt
#include <QDebug>

using namespace domain;

Vehicle::Vehicle(QObject* parent):
    QObject(parent),
    m_type(Vehicle::UnknownType),
    m_state(Vehicle::UnknownState)
{
    qRegisterMetaType<Attitude>("Attitude");
}

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

Attitude Vehicle::attitude() const
{
    return m_attitude;
}

float Vehicle::trueAirSpeed() const
{
    return m_trueAirSpeed;
}

float Vehicle::groundSpeed() const
{
    return m_groundSpeed;
}

float Vehicle::barometricAltitude() const
{
    return m_barometricAltitude;
}

float Vehicle::barometricClimb() const
{
    return m_barometricClimb;
}

int Vehicle::heading() const
{
    return m_heading;
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

void Vehicle::setAttitude(Attitude attitude)
{
    if (m_attitude == attitude) return;

    m_attitude = attitude;
    emit attitudeChanged(attitude);
}

void Vehicle::setTrueAirSpeed(float trueAirSpeed)
{
    if (m_trueAirSpeed == trueAirSpeed) return;

    m_trueAirSpeed = trueAirSpeed;
    emit trueAirSpeedChanged(trueAirSpeed);
}

void Vehicle::setGroundSpeed(float groundSpeed)
{
    if (m_groundSpeed == groundSpeed) return;

    m_groundSpeed = groundSpeed;
    emit groundSpeedChanged(groundSpeed);
}

void Vehicle::setBarometricAltitude(float barometricAltitude)
{
    if (m_barometricAltitude == barometricAltitude) return;

    m_barometricAltitude = barometricAltitude;
    emit barometricAltitudeChanged(barometricAltitude);
}

void Vehicle::setBarometricClimb(float barometricClimb)
{
    if (m_barometricClimb == barometricClimb) return;

    m_barometricClimb = barometricClimb;
    emit barometricClimbChanged(barometricClimb);
}

void Vehicle::setHeading(int heading)
{
    if (m_heading == heading) return;

    m_heading = heading;
    emit headingChanged(heading);
}
