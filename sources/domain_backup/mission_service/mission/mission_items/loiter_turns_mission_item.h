#ifndef LOITER_TURNS_MISSION_ITEM_H
#define LOITER_TURNS_MISSION_ITEM_H

#include "loiter_mission_item.h"

namespace domain
{
    class LoiterTurnsMissionItem: public LoiterMissionItem
    {
        Q_OBJECT

        Q_PROPERTY(int turns READ turns WRITE setTurns NOTIFY turnsChanged)

    public:
        explicit LoiterTurnsMissionItem(Mission* mission);

        int turns() const;

    public slots:
        void setTurns(int turns);

    signals:
        void turnsChanged(int turns);

    private:
        int m_turns;
    };
}

#endif // LOITER_TURNS_MISSION_ITEM_H
