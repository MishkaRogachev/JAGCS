#include "mission.h"

// Qt
#include <QDebug>

using namespace domain;

Mission::Mission(QObject* parent):
    QObject(parent),
    m_itemFactory(this)
{}

int Mission::count() const
{
    return m_items.count();
}

MissionItem* Mission::item(int seq) const
{
    return m_items.value(seq, nullptr);
}

const QList<MissionItem*>& Mission::items() const
{
    return m_items;
}

int Mission::sequence(MissionItem* item) const
{
    return m_items.indexOf(item);
}

MissionItem* Mission::requestItem(int seq, MissionItem::Command command)
{
    if (seq >= m_items.count())
    {
        this->setCount(seq + 1);
    }

    if (m_items.at(seq)->command() != command)
    {
        emit missionItemRemoved(m_items[seq]);
        delete m_items[seq];
        m_items[seq] = new MissionItem(this, command);
        emit missionItemAdded(m_items.last());
    }

    return m_items.at(seq);
}

void Mission::setCount(int count) // TODO: setCount with nullptr mission items
{
    while (count > m_items.count())
    {
        this->addNewMissionItem();
    }

    while (count < m_items.count())
    {
        this->removeMissionItem(m_items.last());
    }
}

void Mission::addNewMissionItem()
{
    uint8_t count = m_items.count();
    m_items.append(m_itemFactory.create(
                       count == 0 ? MissionItem::Home : count == 1 ?
                                                         MissionItem::Takeoff :
                                                         MissionItem::Waypoint));
    emit missionItemAdded(m_items.last());
}

void Mission::removeMissionItem(MissionItem* item)
{
    m_items.removeOne(item);
    emit missionItemRemoved(item);
    delete item;
}
