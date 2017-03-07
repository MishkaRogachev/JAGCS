#include "loiter_turns_mission_item.h"

using namespace domain;

LoiterTurnsMissionItem::LoiterTurnsMissionItem(Mission* mission):
    LoiterMissionItem(mission, Command::LoiterTurns),
    m_turns(0)
{}

int LoiterTurnsMissionItem::turns() const
{
    return m_turns;
}

void LoiterTurnsMissionItem::setTurns(int turns)
{
    if (m_turns == turns) return;

    m_turns = turns;
    emit turnsChanged(turns);
}
