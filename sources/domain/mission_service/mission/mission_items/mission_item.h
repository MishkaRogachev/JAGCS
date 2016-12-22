#ifndef MISSION_ITEM_H
#define MISSION_ITEM_H

#include <QObject>

namespace domain
{
    class Mission;

    class MissionItem: public QObject // TODO: separate with inheritance
    {
        Q_OBJECT

        Q_PROPERTY(unsigned sequence READ sequence CONSTANT)
        Q_PROPERTY(Mission* mission READ mission CONSTANT)

        Q_PROPERTY(Command command READ command WRITE setCommand
                   NOTIFY commandChanged)

        Q_PROPERTY(float pitch READ pitch WRITE setPitch NOTIFY pitchChanged)
        Q_PROPERTY(float yaw READ yaw WRITE setYaw NOTIFY yawChanged)
        Q_PROPERTY(float radius READ radius WRITE setRadius NOTIFY radiusChanged)

        Q_PROPERTY(bool hasPosition READ hasPosition NOTIFY commandChanged)
        Q_PROPERTY(bool current READ isCurrent WRITE setCurrent
                   NOTIFY currentChanged)

    public:
        enum Command
        {
            UnknownCommand = 0,
            Home,
            Takeoff,
            Waypoint,
            Loiter,
            Continue,
            Return,
            Landing
        };

        MissionItem(Mission* mission, Command command);

        Mission* mission() const;
        unsigned sequence() const;

        Command command() const;

        float yaw() const;
        float pitch() const;
        float radius() const;

        bool hasPosition() const;

        bool isCurrent() const;

    public slots:
        void setCommand(Command command);

        void setYaw(float yaw);
        void setPitch(float pitch);
        void setRadius(float radius);

        void setCurrent(bool current);

    signals:
        void commandChanged(Command command);

        void yawChanged(float yaw);
        void pitchChanged(float pitch);
        void radiusChanged(float radius);

        void currentChanged(bool current);

    private:
        Mission* const m_mission;
        Command m_command;
        float m_pitch;
        float m_yaw;
        float m_radius;
        bool m_current;

        Q_ENUM(Command)
    };
}

#endif // MISSION_ITEM_H
