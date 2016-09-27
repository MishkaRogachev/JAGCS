#ifndef VEHICLE_H
#define VEHICLE_H

// Internal
#include "attitude.h"

namespace domain
{
    class Vehicle: public QObject // TODO: system hierarchy
    {
        Q_OBJECT

        Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
        Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)
        Q_PROPERTY(bool autonomous READ autonomous WRITE setAutonomous
                   NOTIFY autonomousChanged)

        Q_PROPERTY(Attitude attitude READ attitude WRITE setAttitude
                   NOTIFY attitudeChanged)

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

        float trueAirSpeed() const;
        float groundSpeed() const;
        float barometricAltitude() const;
        float barometricClimb() const;
        int heading() const;

    public slots:
        void setType(Type type);
        void setState(State state);
        void setAutonomous(bool autonomous);

        void setAttitude(Attitude attitude);

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

        void trueAirSpeedChanged(float trueAirSpeed);
        void groundSpeedChanged(float groundSpeed);
        void barometricAltitudeChanged(float barometricAltitude);
        void barometricClimbChanged(float barometricClimb);
        void headingChanged(int heading);

    private:
        Type m_type;
        State m_state;
        bool m_autonomous;

        Attitude m_attitude;

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
