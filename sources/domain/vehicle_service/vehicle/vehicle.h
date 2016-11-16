#ifndef VEHICLE_H
#define VEHICLE_H

// Internal
#include "attitude.h"
#include "position.h"
#include "gps.h"

namespace domain
{
    class Vehicle: public QObject // TODO: system hierarchy & properly vehicle domain-model
    {
        Q_OBJECT

        Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
        Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)
        Q_PROPERTY(bool autonomous READ autonomous WRITE setAutonomous
                   NOTIFY autonomousChanged)

        Q_PROPERTY(Attitude attitude READ attitude WRITE setAttitude
                   NOTIFY attitudeChanged)
        Q_PROPERTY(Position position READ position WRITE setPosition
                   NOTIFY positionChanged)
        Q_PROPERTY(Position homePosition READ homePosition
                   WRITE setHomePosition NOTIFY homePositionChanged)
        Q_PROPERTY(Gps gps READ gps WRITE setGps NOTIFY gpsChanged)

        Q_PROPERTY(float trueAirSpeed READ trueAirSpeed WRITE setTrueAirSpeed
                   NOTIFY trueAirSpeedChanged)
        Q_PROPERTY(float groundSpeed READ groundSpeed WRITE setGroundSpeed
                   NOTIFY groundSpeedChanged)
        Q_PROPERTY(float barometricAltitude READ barometricAltitude
                   WRITE setBarometricAltitude NOTIFY barometricAltitudeChanged)
        Q_PROPERTY(float barometricClimb READ barometricClimb
                   WRITE setBarometricClimb NOTIFY barometricClimbChanged)
        Q_PROPERTY(int heading READ heading WRITE setHeading
                   NOTIFY headingChanged)

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

        explicit Vehicle(QObject* parent = nullptr);

        Type type() const;
        State state() const;
        bool autonomous() const;

        Attitude attitude() const;
        Position position() const;
        Position homePosition() const;
        Gps gps() const;

        float trueAirSpeed() const;
        float groundSpeed() const;
        float barometricAltitude() const;
        float barometricClimb() const;
        int heading() const;

    public slots:
        void setType(Type type);
        void setState(State state);
        void setAutonomous(bool autonomous);

        void setAttitude(const Attitude& attitude);
        void setPosition(const Position& position);
        void setHomePosition(const Position& homePosition);
        void setGps(const Gps& gps);

        void setTrueAirSpeed(float trueAirSpeed);
        void setGroundSpeed(float groundSpeed);
        void setBarometricAltitude(float barometricAltitude);
        void setBarometricClimb(float barometricClimb);
        void setHeading(int heading);

    signals:
        void typeChanged(Type type);
        void stateChanged(State state);
        void autonomousChanged(bool autonomous);

        void attitudeChanged(Attitude attitude);
        void positionChanged(Position position);
        void homePositionChanged(Position homePosition);
        void gpsChanged(Gps gps);

        void trueAirSpeedChanged(float trueAirSpeed);
        void groundSpeedChanged(float groundSpeed);
        void barometricAltitudeChanged(float barometricAltitude);
        void barometricClimbChanged(float barometricClimb);
        void headingChanged(int heading);

        void setHome(const Position& homePosition);

    private:
        Type m_type;
        State m_state;
        bool m_autonomous;

        Attitude m_attitude;
        Position m_position;
        Position m_homePosition;
        Gps m_gps;

        float m_trueAirSpeed;
        float m_groundSpeed;
        float m_barometricAltitude;
        float m_barometricClimb;
        int m_heading;

        Q_ENUM(Type)
        Q_ENUM(State)
    };
}

#endif // VEHICLE_H
