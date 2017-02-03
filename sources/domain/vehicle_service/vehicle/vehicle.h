#ifndef VEHICLE_H
#define VEHICLE_H

// Internal
#include "attitude.h"
#include "position.h"
#include "gps.h"
#include "power_system.h"

namespace domain
{
    class Mission;

    class Vehicle: public QObject // TODO: system hierarchy & properly vehicle domain-model
    {
        Q_OBJECT

        Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
        Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)
        Q_PROPERTY(bool armed READ isArmed WRITE setArmed NOTIFY armedChanged)

        Q_PROPERTY(bool insAvalible READ insAvalible
                   WRITE setInsAvalible NOTIFY insAvalibleChanged)
        Q_PROPERTY(Attitude attitude READ attitude WRITE setAttitude
                   NOTIFY attitudeChanged)

        Q_PROPERTY(Position position READ position WRITE setPosition
                   NOTIFY positionChanged)
        Q_PROPERTY(Position homePosition READ homePosition
                   WRITE setHomePosition NOTIFY homePositionChanged)

        Q_PROPERTY(bool gpsAvalible READ gpsAvalible
                   WRITE setGpsAvalible NOTIFY gpsAvalibleChanged)
        Q_PROPERTY(Gps gps READ gps WRITE setGps NOTIFY gpsChanged)
        Q_PROPERTY(float groundSpeed READ groundSpeed WRITE setGroundSpeed
                   NOTIFY groundSpeedChanged)

        Q_PROPERTY(PowerSystem powerSystem READ powerSystem
                   WRITE setPowerSystem NOTIFY powerSystemChanged)

        Q_PROPERTY(bool airSpeedAvalible READ airSpeedAvalible
                   WRITE setAirSpeedAvalible NOTIFY airSpeedAvalibleChanged)
        Q_PROPERTY(float indicatedAirSpeed READ indicatedAirSpeed
                   WRITE setIndicatedAirSpeed NOTIFY indicatedAirSpeedChanged)
        Q_PROPERTY(float trueAirSpeed READ trueAirSpeed WRITE setTrueAirSpeed
                   NOTIFY trueAirSpeedChanged)

        Q_PROPERTY(bool barometerAvalible READ barometerAvalible
                   WRITE setBarometerAvalible NOTIFY barometerAvalibleChanged)
        Q_PROPERTY(float barometricAltitude READ barometricAltitude
                   WRITE setBarometricAltitude NOTIFY barometricAltitudeChanged)
        Q_PROPERTY(float barometricClimb READ barometricClimb
                   WRITE setBarometricClimb NOTIFY barometricClimbChanged)

        Q_PROPERTY(bool compasAvalible READ compasAvalible
                   WRITE setCompasAvalible NOTIFY compasAvalibleChanged)
        Q_PROPERTY(int heading READ heading WRITE setHeading
                   NOTIFY headingChanged)

        Q_PROPERTY(bool ahrsAvalible READ ahrsAvalible
                   WRITE setAhrsAvalible NOTIFY ahrsAvalibleChanged)

    public:
        enum Type
        {
            UnknownType = 0,
            FixedWingAircraft
        };

        enum State
        {
            UnknownState = 0,
            Boot,
            Calibrating,
            Standby,
            Active,
            Critical,
            Emergency,
            PowerOff
        };

        Vehicle(uint8_t vehicleId, QObject* parent);
        ~Vehicle() override;

        uint8_t vehicleId() const;

        Type type() const;
        State state() const;
        bool isArmed() const;

        bool insAvalible() const;
        Attitude attitude() const;

        Position position() const;
        Position homePosition() const;

        bool gpsAvalible() const;
        Gps gps() const;
        float groundSpeed() const;

        PowerSystem powerSystem() const;

        bool airSpeedAvalible() const;
        float indicatedAirSpeed() const;
        float trueAirSpeed() const;

        bool barometerAvalible() const;
        float barometricAltitude() const;
        float barometricClimb() const;

        bool compasAvalible() const;
        int heading() const;

        bool ahrsAvalible() const;

        Mission* assignedMission() const;

    public slots:
        void setType(Type type);
        void setState(State state);
        void setArmed(bool armed);

        void setInsAvalible(bool insAvalible);
        void setAttitude(const Attitude& attitude);

        void setPosition(const Position& position);
        void setHomePosition(const Position& homePosition);

        void setGpsAvalible(bool gpsAvalible);
        void setGps(const Gps& gps);
        void setGroundSpeed(float groundSpeed);

        void setPowerSystem(const PowerSystem& powerSystem);

        void setAirSpeedAvalible(bool airSpeedAvalible);
        void setIndicatedAirSpeed(float indicatedAirSpeed);
        void setTrueAirSpeed(float trueAirSpeed);

        void setBarometerAvalible(bool barometerAvalible);
        void setBarometricAltitude(float barometricAltitude);
        void setBarometricClimb(float barometricClimb);

        void setCompasAvalible(bool compasAvalible);
        void setHeading(int heading);

        void setAhrsAvalible(bool ahrsAvalible);

        void assignMission(Mission* mission);
        void unassignMission();

    signals:
        void typeChanged(Type type);
        void stateChanged(State state);
        void armedChanged(bool armed);

        void insAvalibleChanged(bool insAvalible);
        void attitudeChanged(Attitude attitude);

        void positionChanged(Position position);
        void homePositionChanged(Position homePosition);

        void gpsAvalibleChanged(bool gpsAvalible);
        void gpsChanged(Gps gps);
        void groundSpeedChanged(float groundSpeed);

        void powerSystemChanged(PowerSystem powerSystem);

        void airSpeedAvalibleChanged(bool airSpeedAvalible);
        void indicatedAirSpeedChanged(float indicatedAirSpeed);
        void trueAirSpeedChanged(float trueAirSpeed);

        void barometerAvalibleChanged(bool barometerAvalible);
        void barometricAltitudeChanged(float barometricAltitude);
        void barometricClimbChanged(float barometricClimb);

        void compasAvalibleChanged(bool compasAvalible);
        void headingChanged(int heading);

        void ahrsAvalibleChanged(bool ahrsAvalible);

        void assignedMissionChanged(Mission* mission);

        void commandArm(bool arm);
        void commandSetHome(const Position& homePosition);

    private:
        uint8_t m_vehicleId;

        Type m_type;
        State m_state;
        bool m_armed;

        bool m_insAvalible;
        Attitude m_attitude;

        Position m_position;
        Position m_homePosition;

        bool m_gpsAvalible;
        Gps m_gps;
        float m_groundSpeed;

        PowerSystem m_powerSystem;

        bool m_airSpeedAvalible;
        float m_indicatedAirSpeed;
        float m_trueAirSpeed;

        bool m_barometerAvalible;
        float m_barometricAltitude;
        float m_barometricClimb;

        bool m_compasAvalible;
        int m_heading;

        bool m_ahrsAvalible;

        Mission* m_assignedMission;

        Q_ENUM(Type)
        Q_ENUM(State)
    };
}

#endif // VEHICLE_H
