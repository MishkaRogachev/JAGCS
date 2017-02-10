#include "mission_item.h"

// QT
#include <QDebug>

// Internal
#include "mission.h"
#include "mission_item_factory.h"

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

int MissionItem::sequence() const
{
    return m_mission->sequence((MissionItem*)this);
}

bool MissionItem::isFirst() const
{
    return this->sequence() == 0;
}

bool MissionItem::isLast() const
{
    return int(this->sequence()) == m_mission->count() - 1;
}

Command MissionItem::command() const
{
    return m_command;
}

QList<Command> MissionItem::avalibleCommands() const
{
    QList<Command> list;

    if (this->isFirst())
    {
        list << Command::Home;
    }
    else
    {
        list << Command::Takeoff << Command::Waypoint <<
                Command::LoiterAltitude << Command::LoiterTurns <<
                Command::Continue << Command::Return << Command::Landing;
    }

    return list;
}

bool MissionItem::isCurrent() const
{
    return m_current;
}

void MissionItem::clone(MissionItem* mission)
{
    this->setCurrent(mission->isCurrent());
}

void MissionItem::replaceWithCommand(Command command)
{
    if (m_command == command || command == Command::UnknownCommand) return;

    MissionItemFactory factory(m_mission);
    MissionItem* newItem = factory.create(command);
    newItem->clone(this);
    m_mission->setMissionItem(this->sequence(), newItem);
}

void MissionItem::moveUp()
{
    unsigned index = this->sequence();
    m_mission->exchange(index, index - 1);
}

void MissionItem::moveDown()
{
    unsigned index = this->sequence();
    m_mission->exchange(index, index + 1);
}

void MissionItem::setCurrent(bool current)
{
    if (m_current == current) return;

    m_current = current;
    emit currentChanged(current);
}
