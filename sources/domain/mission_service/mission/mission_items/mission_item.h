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
        Q_PROPERTY(Command command READ command CONSTANT)

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

        bool isCurrent() const;

        virtual void clone(MissionItem* mission);

    public slots:
        void replaceWithCommand(Command command);

        void setCurrent(bool current);

    signals:
        void currentChanged(bool current);

    private:
        Mission* const m_mission;
        const Command m_command;
        bool m_current;

        Q_ENUM(Command)
    };
}

#endif // MISSION_ITEM_H
