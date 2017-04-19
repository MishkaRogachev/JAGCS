#include "aerial_vehicle.h"

// Qt
#include <QDebug>

using namespace domain;

AerialVehicle::AerialVehicle(Type type, QObject* parent):
    BaseVehicle(type, parent),
    m_airSpeedAvalible(false),
    m_indicatedAirSpeed(0),
    m_trueAirSpeed(0),
    m_barometerAvalible(false),
    m_barometricAltitude(0),
    m_barometricClimb(0),
    m_rangeFinderAvalible(false),
    m_ahrsAvalible(false)
{
    connect(this, &BaseVehicle::homePositionChanged, this,
            [this]() { emit homeAltitudeChanged(this->homeAltitude()); } );
}

AerialVehicle::~AerialVehicle()
{}

bool AerialVehicle::airSpeedAvalible() const
{
    return m_airSpeedAvalible;
}

float AerialVehicle::indicatedAirSpeed() const
{
    return m_indicatedAirSpeed;
}

float AerialVehicle::trueAirSpeed() const
{
    return m_trueAirSpeed;
}

Wind AerialVehicle::wind() const
{
    return m_wind;
}

bool AerialVehicle::barometerAvalible() const
{
    return m_barometerAvalible;
}

float AerialVehicle::barometricAltitude() const
{
    return m_barometricAltitude;
}

float AerialVehicle::barometricClimb() const
{
    return m_barometricClimb;
}

float AerialVehicle::homeAltitude() const
{
    return m_homePosition.coordinate().type() == QGeoCoordinate::Coordinate3D ?
                m_homePosition.coordinate().altitude() : 0;
}

bool AerialVehicle::rangeFinderAvalible() const
{
    return m_rangeFinderAvalible;
}

bool AerialVehicle::ahrsAvalible() const
{
    return m_ahrsAvalible;
}

void AerialVehicle::setAirSpeedAvalible(bool airSpeedAvalible)
{
    if (m_airSpeedAvalible == airSpeedAvalible) return;

    m_airSpeedAvalible = airSpeedAvalible;
    emit airSpeedAvalibleChanged(airSpeedAvalible);
}

void AerialVehicle::setIndicatedAirSpeed(float indicatedAirSpeed)
{
    if (qFuzzyCompare(m_indicatedAirSpeed, indicatedAirSpeed)) return;

    m_indicatedAirSpeed = indicatedAirSpeed;
    emit indicatedAirSpeedChanged(indicatedAirSpeed);
}

void AerialVehicle::setTrueAirSpeed(float trueAirSpeed)
{
    if (qFuzzyCompare(m_trueAirSpeed, trueAirSpeed)) return;

    m_trueAirSpeed = trueAirSpeed;
    emit trueAirSpeedChanged(trueAirSpeed);
}

void AerialVehicle::setWind(Wind wind)
{
    if (m_wind == wind) return;

    m_wind = wind;
    emit windChanged(wind);
}

void AerialVehicle::setBarometerAvalible(bool barometerAvalible)
{
    if (m_barometerAvalible == barometerAvalible) return;

    m_barometerAvalible = barometerAvalible;
    emit barometerAvalibleChanged(barometerAvalible);
}

void AerialVehicle::setBarometricAltitude(float barometricAltitude)
{
    if (qFuzzyCompare(m_barometricAltitude, barometricAltitude)) return;

    m_barometricAltitude = barometricAltitude;
    emit barometricAltitudeChanged(barometricAltitude);
}

void AerialVehicle::setBarometricClimb(float barometricClimb)
{
    if (qFuzzyCompare(m_barometricClimb, barometricClimb)) return;

    m_barometricClimb = barometricClimb;
    emit barometricClimbChanged(barometricClimb);
}

void AerialVehicle::setRangeFinderAvalible(bool rangeFinderAvalible)
{
    if (m_rangeFinderAvalible == rangeFinderAvalible) return;

    m_rangeFinderAvalible = rangeFinderAvalible;
    emit rangeFinderAvalibleChanged(rangeFinderAvalible);
}

void AerialVehicle::setAhrsAvalible(bool ahrsAvalible)
{
    if (m_ahrsAvalible == ahrsAvalible) return;

    m_ahrsAvalible = ahrsAvalible;
    emit ahrsAvalibleChanged(ahrsAvalible);
}
