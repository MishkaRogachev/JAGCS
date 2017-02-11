#include "base_vehicle.h"

using namespace domain;

BaseVehicle::BaseVehicle(uint8_t vehicleId, int type, QObject* parent):
    AbstractVehicle(vehicleId, type, parent),
    m_state(BaseVehicle::UnknownState),
    m_armed(false),
    m_autonomous(false),
    m_guided(false),
    m_stabilized(false),
    m_insAvalible(false),
    m_gpsAvalible(false),
    m_groundSpeed(0),
    m_compasAvalible(false),
    m_heading(0)
{}

BaseVehicle::State BaseVehicle::state() const
{
    return m_state;
}

bool BaseVehicle::isArmed() const
{
    return m_armed;
}

bool BaseVehicle::autonomous() const
{
    return m_autonomous;
}

bool BaseVehicle::guided() const
{
    return m_guided;
}

bool BaseVehicle::stabilized() const
{
    return m_stabilized;
}

bool BaseVehicle::insAvalible() const
{
    return m_insAvalible;
}

Attitude BaseVehicle::attitude() const
{
    return m_attitude;
}

Position BaseVehicle::position() const
{
    return m_position;
}

Position BaseVehicle::homePosition() const
{
    return m_homePosition;
}

float BaseVehicle::homeDirection() const
{
    if (m_position.coordinate().isValid() &&
        m_homePosition.coordinate().isValid())
    {
        return m_position.coordinate().azimuthTo(m_homePosition.coordinate());
    }
    return -1;
}

float BaseVehicle::homeDistance() const
{
    if (m_position.coordinate().isValid() &&
        m_homePosition.coordinate().isValid())
    {
        return m_position.coordinate().distanceTo(m_homePosition.coordinate());
    }
    return -1;
}

bool BaseVehicle::gpsAvalible() const
{
    return m_gpsAvalible;
}

Gps BaseVehicle::gps() const
{
    return m_gps;
}

float BaseVehicle::groundSpeed() const
{
    return m_groundSpeed;
}

PowerSystem BaseVehicle::powerSystem() const
{
    return m_powerSystem;
}

bool BaseVehicle::compasAvalible() const
{
    return m_compasAvalible;
}

int BaseVehicle::heading() const
{
    return m_heading;
}

void BaseVehicle::setState(BaseVehicle::State state)
{
    if (m_state == state) return;

    m_state = state;
    emit stateChanged(state);
}

void BaseVehicle::setArmed(bool armed)
{
    if (m_armed == armed) return;

    m_armed = armed;
    emit armedChanged(armed);
}

void BaseVehicle::setAutonomous(bool autonomous)
{
    if (m_autonomous == autonomous) return;

    m_autonomous = autonomous;
    emit autonomousChanged(autonomous);
}

void BaseVehicle::setGuided(bool guided)
{
    if (m_guided == guided) return;

    m_guided = guided;
    emit guidedChanged(guided);
}

void BaseVehicle::setStabilized(bool stabilized)
{
    if (m_stabilized == stabilized) return;

    m_stabilized = stabilized;
    emit stabilizedChanged(stabilized);
}

void BaseVehicle::setInsAvalible(bool insAvalible)
{
    if (m_insAvalible == insAvalible) return;

    m_insAvalible = insAvalible;
    emit insAvalibleChanged(insAvalible);
}

void BaseVehicle::setAttitude(const Attitude& attitude)
{
    if (m_attitude == attitude) return;

    m_attitude = attitude;
    emit attitudeChanged(attitude);
}

void BaseVehicle::setPosition(const Position& position)
{
    if (m_position == position) return;

    m_position = position;
    emit positionChanged(position);
    emit homeDirectionChanged(this->homeDirection());
    emit homeDistanceChanged(this->homeDistance());
}

void BaseVehicle::setHomePosition(const Position& homePosition)
{
    if (m_homePosition == homePosition) return;

    m_homePosition = homePosition;
    emit homePositionChanged(homePosition);
    emit homeDirectionChanged(this->homeDirection());
    emit homeDistanceChanged(this->homeDistance());
}

void BaseVehicle::setGpsAvalible(bool gpsAvalible)
{
    if (m_gpsAvalible == gpsAvalible) return;

    m_gpsAvalible = gpsAvalible;
    emit gpsAvalibleChanged(gpsAvalible);
}

void BaseVehicle::setGps(const Gps& gps)
{
    if (m_gps == gps) return;

    m_gps = gps;
    emit gpsChanged(gps);
}

void BaseVehicle::setGroundSpeed(float groundSpeed)
{
    if (qFuzzyCompare(m_groundSpeed, groundSpeed)) return;

    m_groundSpeed = groundSpeed;
    emit groundSpeedChanged(groundSpeed);
}

void BaseVehicle::setPowerSystem(const PowerSystem& powerSystem)
{
    if (m_powerSystem == powerSystem) return;

    m_powerSystem = powerSystem;
    emit powerSystemChanged(powerSystem);
}

void BaseVehicle::setCompasAvalible(bool compasAvalible)
{
    if (m_compasAvalible == compasAvalible) return;

    m_compasAvalible = compasAvalible;
    emit compasAvalibleChanged(compasAvalible);
}

void BaseVehicle::setHeading(int heading)
{
    if (m_heading == heading) return;

    m_heading = heading;
    emit headingChanged(heading);
}
