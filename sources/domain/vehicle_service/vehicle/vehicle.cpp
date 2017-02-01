#include "vehicle.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle_service.h"

using namespace domain;

Vehicle::Vehicle(uint8_t vehicleId, QObject* parent):
    QObject(parent),
    m_vehicleId(vehicleId),
    m_type(Vehicle::UnknownType),
    m_state(Vehicle::UnknownState),
    m_armed(false),
    m_indicatedAirSpeed(0),
    m_trueAirSpeed(0),
    m_groundSpeed(0),
    m_barometricAltitude(0),
    m_barometricClimb(0),
    m_heading(0),
    m_assignedMission(nullptr)
{}

Vehicle::~Vehicle()
{
    if (m_assignedMission) this->unassignMission();
}

uint8_t Vehicle::vehicleId() const
{
    return m_vehicleId;
}

Vehicle::Type Vehicle::type() const
{
    return m_type;
}

Vehicle::State Vehicle::state() const
{
    return m_state;
}

bool Vehicle::isArmed() const
{
    return m_armed;
}

Attitude Vehicle::attitude() const
{
    return m_attitude;
}

Position Vehicle::position() const
{
    return m_position;
}

Position Vehicle::homePosition() const
{
    return m_homePosition;
}

Gps Vehicle::gps() const
{
    return m_gps;
}

PowerSystem Vehicle::powerSystem() const
{
    return m_powerSystem;
}

float Vehicle::indicatedAirSpeed() const
{
    return m_indicatedAirSpeed;
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

Mission* Vehicle::assignedMission() const
{
    return m_assignedMission;
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

void Vehicle::setArmed(bool armed)
{
    if (m_armed == armed) return;

    m_armed = armed;
    emit armedChanged(armed);
}

void Vehicle::setAttitude(const Attitude& attitude)
{
    if (m_attitude == attitude) return;

    m_attitude = attitude;
    emit attitudeChanged(attitude);
}

void Vehicle::setPosition(const Position& position)
{
    if (m_position == position) return;

    m_position = position;
    emit positionChanged(position);
}

void Vehicle::setHomePosition(const Position& homePosition)
{
    if (m_homePosition == homePosition) return;

    m_homePosition = homePosition;
    emit homePositionChanged(homePosition);
}

void Vehicle::setGps(const Gps& gps)
{
    if (m_gps == gps) return;

    m_gps = gps;
    emit gpsChanged(gps);
}

void Vehicle::setPowerSystem(const PowerSystem& powerSystem)
{
    if (m_powerSystem == powerSystem) return;

    m_powerSystem = powerSystem;
    emit powerSystemChanged(powerSystem);
}

void Vehicle::setIndicatedAirSpeed(float indicatedAirSpeed)
{
    if (m_indicatedAirSpeed == indicatedAirSpeed) return;

    m_indicatedAirSpeed = indicatedAirSpeed;
    emit indicatedAirSpeedChanged(indicatedAirSpeed);
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

void Vehicle::unassignMission()
{
    this->assignMission(nullptr);
}

void Vehicle::assignMission(Mission* mission)
{
    if (m_assignedMission == mission) return;

    if (m_assignedMission)
    {
        m_assignedMission->unassignVehicle();
    }

    m_assignedMission = mission;

    if (m_assignedMission)
    {
        m_assignedMission->assignVehicle(this);
    }

    emit assignedMissionChanged(mission);
}
