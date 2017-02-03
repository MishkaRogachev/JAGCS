#include "vehicle.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle_service.h"
#include "mission.h"

using namespace domain;

Vehicle::Vehicle(uint8_t vehicleId, QObject* parent):
    QObject(parent),
    m_vehicleId(vehicleId),
    m_type(Vehicle::UnknownType),
    m_state(Vehicle::UnknownState),
    m_armed(false),
    m_insAvalible(false),
    m_gpsAvalible(false),
    m_groundSpeed(0),
    m_airSpeedAvalible(false),
    m_indicatedAirSpeed(0),
    m_trueAirSpeed(0),
    m_barometerAvalible(false),
    m_barometricAltitude(0),
    m_barometricClimb(0),
    m_compasAvalible(false),
    m_heading(0),
    m_ahrsAvalible(false),
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

bool Vehicle::insAvalible() const
{
    return m_insAvalible;
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

bool Vehicle::gpsAvalible() const
{
    return m_gpsAvalible;
}

Gps Vehicle::gps() const
{
    return m_gps;
}

float Vehicle::groundSpeed() const
{
    return m_groundSpeed;
}

PowerSystem Vehicle::powerSystem() const
{
    return m_powerSystem;
}

bool Vehicle::airSpeedAvalible() const
{
    return m_airSpeedAvalible;
}

float Vehicle::indicatedAirSpeed() const
{
    return m_indicatedAirSpeed;
}

float Vehicle::trueAirSpeed() const
{
    return m_trueAirSpeed;
}

bool Vehicle::barometerAvalible() const
{
    return m_barometerAvalible;
}

float Vehicle::barometricAltitude() const
{
    return m_barometricAltitude;
}

float Vehicle::barometricClimb() const
{
    return m_barometricClimb;
}

bool Vehicle::compasAvalible() const
{
    return m_compasAvalible;
}

int Vehicle::heading() const
{
    return m_heading;
}

bool Vehicle::ahrsAvalible() const
{
    return m_ahrsAvalible;
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

void Vehicle::setInsAvalible(bool insAvalible)
{
    if (m_insAvalible == insAvalible) return;

    m_insAvalible = insAvalible;
    emit insAvalibleChanged(insAvalible);
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

void Vehicle::setGpsAvalible(bool gpsAvalible)
{
    if (m_gpsAvalible == gpsAvalible) return;

    m_gpsAvalible = gpsAvalible;
    emit gpsAvalibleChanged(gpsAvalible);
}

void Vehicle::setGps(const Gps& gps)
{
    if (m_gps == gps) return;

    m_gps = gps;
    emit gpsChanged(gps);
}

void Vehicle::setGroundSpeed(float groundSpeed)
{
    if (qFuzzyCompare(m_groundSpeed, groundSpeed)) return;

    m_groundSpeed = groundSpeed;
    emit groundSpeedChanged(groundSpeed);
}

void Vehicle::setPowerSystem(const PowerSystem& powerSystem)
{
    if (m_powerSystem == powerSystem) return;

    m_powerSystem = powerSystem;
    emit powerSystemChanged(powerSystem);
}

void Vehicle::setAirSpeedAvalible(bool airSpeedAvalible)
{
    if (m_airSpeedAvalible == airSpeedAvalible) return;

    m_airSpeedAvalible = airSpeedAvalible;
    emit airSpeedAvalibleChanged(airSpeedAvalible);
}

void Vehicle::setIndicatedAirSpeed(float indicatedAirSpeed)
{
    if (qFuzzyCompare(m_indicatedAirSpeed, indicatedAirSpeed)) return;

    m_indicatedAirSpeed = indicatedAirSpeed;
    emit indicatedAirSpeedChanged(indicatedAirSpeed);
}

void Vehicle::setTrueAirSpeed(float trueAirSpeed)
{
    if (qFuzzyCompare(m_trueAirSpeed, trueAirSpeed)) return;

    m_trueAirSpeed = trueAirSpeed;
    emit trueAirSpeedChanged(trueAirSpeed);
}

void Vehicle::setBarometerAvalible(bool barometerAvalible)
{
    if (m_barometerAvalible == barometerAvalible) return;

    m_barometerAvalible = barometerAvalible;
    emit barometerAvalibleChanged(barometerAvalible);
}

void Vehicle::setBarometricAltitude(float barometricAltitude)
{
    if (qFuzzyCompare(m_barometricAltitude, barometricAltitude)) return;

    m_barometricAltitude = barometricAltitude;
    emit barometricAltitudeChanged(barometricAltitude);
}

void Vehicle::setBarometricClimb(float barometricClimb)
{
    if (qFuzzyCompare(m_barometricClimb, barometricClimb)) return;

    m_barometricClimb = barometricClimb;
    emit barometricClimbChanged(barometricClimb);
}

void Vehicle::setCompasAvalible(bool compasAvalible)
{
    if (m_compasAvalible == compasAvalible) return;

    m_compasAvalible = compasAvalible;
    emit compasAvalibleChanged(compasAvalible);
}

void Vehicle::setHeading(int heading)
{
    if (m_heading == heading) return;

    m_heading = heading;
    emit headingChanged(heading);
}

void Vehicle::setAhrsAvalible(bool ahrsAvalible)
{
    if (m_ahrsAvalible == ahrsAvalible) return;

    m_ahrsAvalible = ahrsAvalible;
    emit ahrsAvalibleChanged(ahrsAvalible);
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
