#include "vehicle.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle_service.h"
#include "mission.h"

using namespace domain;

Vehicle::Vehicle(uint8_t vehicleId, Type type, QObject* parent):
    AbstractVehicle(vehicleId, type, parent),
    m_state(Vehicle::UnknownState),
    m_armed(false),
    m_autonomous(false),
    m_guided(false),
    m_stabilized(false),
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
    m_rangeFinderAvalible(false),
    m_ahrsAvalible(false)
{}

Vehicle::~Vehicle()
{}

Vehicle::State Vehicle::state() const
{
    return m_state;
}

bool Vehicle::isArmed() const
{
    return m_armed;
}

bool Vehicle::autonomous() const
{
    return m_autonomous;
}

bool Vehicle::guided() const
{
    return m_guided;
}

bool Vehicle::stabilized() const
{
    return m_stabilized;
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

float Vehicle::homeDirection() const
{
    if (m_position.coordinate().isValid() &&
        m_homePosition.coordinate().isValid())
    {
        return m_position.coordinate().azimuthTo(m_homePosition.coordinate());
    }
    return -1;
}

float Vehicle::homeDistance() const
{
    if (m_position.coordinate().isValid() &&
        m_homePosition.coordinate().isValid())
    {
        return m_position.coordinate().distanceTo(m_homePosition.coordinate());
    }
    return -1;
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

Wind Vehicle::wind() const
{
    return m_wind;
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

bool Vehicle::rangeFinderAvalible() const
{
    return m_rangeFinderAvalible;
}

bool Vehicle::ahrsAvalible() const
{
    return m_ahrsAvalible;
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

void Vehicle::setAutonomous(bool autonomous)
{
    if (m_autonomous == autonomous) return;

    m_autonomous = autonomous;
    emit autonomousChanged(autonomous);
}

void Vehicle::setGuided(bool guided)
{
    if (m_guided == guided) return;

    m_guided = guided;
    emit guidedChanged(guided);
}

void Vehicle::setStabilized(bool stabilized)
{
    if (m_stabilized == stabilized) return;

    m_stabilized = stabilized;
    emit stabilizedChanged(stabilized);
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
    emit homeDirectionChanged(this->homeDirection());
    emit homeDistanceChanged(this->homeDistance());
}

void Vehicle::setHomePosition(const Position& homePosition)
{
    if (m_homePosition == homePosition) return;

    m_homePosition = homePosition;
    emit homePositionChanged(homePosition);
    emit homeDirectionChanged(this->homeDirection());
    emit homeDistanceChanged(this->homeDistance());
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

void Vehicle::setWind(Wind wind)
{
    if (m_wind == wind) return;

    m_wind = wind;
    emit windChanged(wind);
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

void Vehicle::setRangeFinderAvalible(bool rangeFinderAvalible)
{
    if (m_rangeFinderAvalible == rangeFinderAvalible) return;

    m_rangeFinderAvalible = rangeFinderAvalible;
    emit rangeFinderAvalibleChanged(rangeFinderAvalible);
}

void Vehicle::setAhrsAvalible(bool ahrsAvalible)
{
    if (m_ahrsAvalible == ahrsAvalible) return;

    m_ahrsAvalible = ahrsAvalible;
    emit ahrsAvalibleChanged(ahrsAvalible);
}
