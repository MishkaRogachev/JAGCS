#include "abstract_mission_item.h"

// QT
#include <QDebug>

// Internal
#include "mission.h"
#include "mission_item_factory.h"

using namespace domain;

AbstractMissionItem::AbstractMissionItem(Mission* mission, Command command):
    QObject(mission),
    m_mission(mission),
    m_command(command)
{}

Mission* AbstractMissionItem::mission() const
{
    return m_mission;
}

int AbstractMissionItem::sequence() const
{
    return m_mission->sequence((AbstractMissionItem*)this);
}

bool AbstractMissionItem::isFirst() const
{
    return this->sequence() == 0;
}

bool AbstractMissionItem::isLast() const
{
    return int(this->sequence()) == m_mission->count() - 1;
}

Command AbstractMissionItem::command() const
{
    return m_command;
}

QList<Command> AbstractMissionItem::avalibleCommands() const
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

bool AbstractMissionItem::isCurrent() const
{
    return this->sequence() == m_mission->currentIndex();
}

void AbstractMissionItem::replaceWithCommand(Command command)
{
    if (m_command == command || command == Command::UnknownCommand) return;

    MissionItemFactory factory(m_mission);
    AbstractMissionItem* newItem = factory.create(command);
    newItem->clone(this);
    m_mission->setMissionItem(this->sequence(), newItem);
}

void AbstractMissionItem::moveUp()
{
    unsigned index = this->sequence();
    m_mission->exchange(index, index - 1);
}

void AbstractMissionItem::moveDown()
{
    unsigned index = this->sequence();
    m_mission->exchange(index, index + 1);
}
