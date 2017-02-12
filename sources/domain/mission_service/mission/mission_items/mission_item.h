#ifndef MISSION_ITEM_H
#define MISSION_ITEM_H

// Qt
#include <QObject>

// Internal
#include "command.h"

namespace domain
{
    class Mission;

    class MissionItem: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(int sequence READ sequence CONSTANT)
        Q_PROPERTY(Mission* mission READ mission CONSTANT)
        Q_PROPERTY(Command command READ command CONSTANT)

        Q_PROPERTY(bool current READ isCurrent WRITE setCurrent
                   NOTIFY currentChanged)

    public:
        MissionItem(Mission* mission, Command command);

        int sequence() const;
        Q_INVOKABLE bool isFirst() const;
        Q_INVOKABLE bool isLast() const;

        Mission* mission() const;

        Command command() const;
        Q_INVOKABLE QList<Command> avalibleCommands() const;

        bool isCurrent() const;

        virtual void clone(MissionItem* mission);

    public slots:
        void replaceWithCommand(Command command);

        void moveUp();
        void moveDown();

        void setCurrent(bool current);

    signals:
        void currentChanged(bool current);

    private:
        Mission* const m_mission;
        const Command m_command;
        bool m_current;
    };
}

#endif // MISSION_ITEM_H
