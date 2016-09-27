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

    public slots:
        void setType(Type type);
        void setState(State state);
        void setAutonomous(bool autonomous);

        void setAttitude(Attitude attitude);

    signals:
        void typeChanged(Type type);
        void stateChanged(State state);
        void autonomousChanged(bool autonomous);

        void attitudeChanged(Attitude attitude);

    private:
        Type m_type;
        State m_state;
        bool m_autonomous;

        Attitude m_attitude;

        Q_ENUM(Type)
        Q_ENUM(State)
    };
}

#endif // VEHICLE_H
