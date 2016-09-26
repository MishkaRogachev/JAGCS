#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>

namespace domain
{
    class Vehicle: public QObject // TODO: system hierarchy
    {
        Q_OBJECT

        Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
        Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)
        Q_PROPERTY(bool autonomous READ autonomous WRITE setAutonomous
                   NOTIFY autonomousChanged)

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

    public slots:
        void setType(Type type);
        void setState(State state);
        void setAutonomous(bool autonomous);

    signals:
        void typeChanged(Type type);
        void stateChanged(State state);
        void autonomousChanged(bool autonomous);

    private:
        Type m_type;
        State m_state;
        bool m_autonomous;

        Q_ENUM(Type)
        Q_ENUM(State)
    };
}

#endif // VEHICLE_H
