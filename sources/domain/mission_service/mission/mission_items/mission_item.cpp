#include "mission_item.h"

// QT
#include <QDebug>

// Internal
#include "mission.h"

using namespace domain;

MissionItem::MissionItem(Mission* mission, Command command):
    QObject(mission),
    m_mission(mission),
    m_command(command),
    m_current(false)
{}

Mission* MissionItem::mission() const
{
    return m_mission;
}

unsigned MissionItem::sequence() const
{
    return m_mission->sequence((MissionItem*)this);
}

MissionItem::Command MissionItem::command() const
{
    return m_command;
}

bool MissionItem::isCurrent() const
{
    return m_current;
}

void MissionItem::replaceWithCommand(MissionItem::Command command)
{
    if (m_command == command) return;

    // TODO: relace witch command
}

void MissionItem::setCurrent(bool current)
{
    if (m_current == current) return;

    m_current = current;
    emit currentChanged(current);
}
