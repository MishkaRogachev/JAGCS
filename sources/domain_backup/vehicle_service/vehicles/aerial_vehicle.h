#ifndef AERIAL_VEHICLE_H
#define AERIAL_VEHICLE_H

// Internal
#include "base_vehicle.h"

#include "wind.h"

namespace domain
{
    class AerialVehicle: public BaseVehicle
    {
        Q_OBJECT

        Q_PROPERTY(bool airSpeedAvalible READ airSpeedAvalible
                   WRITE setAirSpeedAvalible NOTIFY airSpeedAvalibleChanged)
        Q_PROPERTY(float indicatedAirSpeed READ indicatedAirSpeed
                   WRITE setIndicatedAirSpeed NOTIFY indicatedAirSpeedChanged)
        Q_PROPERTY(float trueAirSpeed READ trueAirSpeed WRITE setTrueAirSpeed
                   NOTIFY trueAirSpeedChanged)
        Q_PROPERTY(Wind wind READ wind WRITE setWind NOTIFY windChanged)

        Q_PROPERTY(bool barometerAvalible READ barometerAvalible
                   WRITE setBarometerAvalible NOTIFY barometerAvalibleChanged)
        Q_PROPERTY(float barometricAltitude READ barometricAltitude
                   WRITE setBarometricAltitude NOTIFY barometricAltitudeChanged)
        Q_PROPERTY(float barometricClimb READ barometricClimb
                   WRITE setBarometricClimb NOTIFY barometricClimbChanged)

        Q_PROPERTY(float homeAltitude READ homeAltitude
                   NOTIFY homeAltitudeChanged)

        Q_PROPERTY(bool rangeFinderAvalible READ rangeFinderAvalible
                   WRITE setRangeFinderAvalible NOTIFY rangeFinderAvalibleChanged)

        Q_PROPERTY(bool ahrsAvalible READ ahrsAvalible
                   WRITE setAhrsAvalible NOTIFY ahrsAvalibleChanged)

    public:
        enum Type
        {
            FixedWingAircraft = UnknownType + 1,
            Multirotor,
            Helicopter,
            Airship,
            Vtol
        };

        AerialVehicle(uint8_t vehicleId, Type type, QObject* parent);
        ~AerialVehicle() override;

        bool airSpeedAvalible() const;
        float indicatedAirSpeed() const;
        float trueAirSpeed() const;
        Wind wind() const;

        bool barometerAvalible() const;
        float barometricAltitude() const;
        float barometricClimb() const;

        float homeAltitude() const;

        bool rangeFinderAvalible() const;

        bool ahrsAvalible() const;

    public slots:
        void setAirSpeedAvalible(bool airSpeedAvalible);
        void setIndicatedAirSpeed(float indicatedAirSpeed);
        void setTrueAirSpeed(float trueAirSpeed);
        void setWind(Wind wind);

        void setBarometerAvalible(bool barometerAvalible);
        void setBarometricAltitude(float barometricAltitude);
        void setBarometricClimb(float barometricClimb);

        void setRangeFinderAvalible(bool rangeFinderAvalible);

        void setAhrsAvalible(bool ahrsAvalible);

    signals:
        void airSpeedAvalibleChanged(bool airSpeedAvalible);
        void indicatedAirSpeedChanged(float indicatedAirSpeed);
        void trueAirSpeedChanged(float trueAirSpeed);
        void windChanged(Wind wind);

        void barometerAvalibleChanged(bool barometerAvalible);
        void barometricAltitudeChanged(float barometricAltitude);
        void barometricClimbChanged(float barometricClimb);

        void homeAltitudeChanged(float homeAltitude);

        void rangeFinderAvalibleChanged(bool rangeFinderAvalible);

        void ahrsAvalibleChanged(bool ahrsAvalible);

    private:
        bool m_airSpeedAvalible;
        float m_indicatedAirSpeed;
        float m_trueAirSpeed;
        Wind m_wind;

        bool m_barometerAvalible;
        float m_barometricAltitude;
        float m_barometricClimb;

        bool m_rangeFinderAvalible;

        bool m_ahrsAvalible;

        Q_ENUM(Type)
    };
}

#endif // AERIAL_VEHICLE_H
