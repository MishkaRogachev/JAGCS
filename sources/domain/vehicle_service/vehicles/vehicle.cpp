#include "vehicle.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle_service.h"
#include "mission.h"

using namespace domain;

Vehicle::Vehicle(uint8_t vehicleId, Type type, QObject* parent):
    BaseVehicle(vehicleId, type, parent),
    m_airSpeedAvalible(false),
    m_indicatedAirSpeed(0),
    m_trueAirSpeed(0),
    m_barometerAvalible(false),
    m_barometricAltitude(0),
    m_barometricClimb(0),
    m_rangeFinderAvalible(false),
    m_ahrsAvalible(false)
{}

Vehicle::~Vehicle()
{}

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

bool Vehicle::rangeFinderAvalible() const
{
    return m_rangeFinderAvalible;
}

bool Vehicle::ahrsAvalible() const
{
    return m_ahrsAvalible;
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
