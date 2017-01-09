#include "mission.h"

// Qt
#include <QDebug>

// Internal
#include "mission_item_factory.h"

using namespace domain;

Mission::Mission(QObject* parent):
    QObject(parent)
{}

Mission::~Mission()
{
    while (!m_items.isEmpty())
    {
        delete m_items.takeLast();
    }
    emit missionItemsChanged(m_items);
}

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

MissionItem* Mission::take(int seq)
{
    MissionItem* item = m_items.takeAt(seq);
    emit missionItemsChanged(m_items);
    return item;
}

void Mission::setCount(int count)
{
    while (m_items.count() < count)
    {
        m_items.append(nullptr);
    }

    while (m_items.count() > count)
    {
        delete m_items.takeLast();
    }

    emit missionItemsChanged(m_items);
}

void Mission::setMissionItem(int seq, MissionItem* item)
{
    if (seq >= m_items.count())
    {
        this->setCount(seq + 1);
    }

    MissionItem* oldItem = m_items[seq];

    m_items[seq] = item;
    emit missionItemsChanged(m_items);

    if (oldItem) delete oldItem;
}

void Mission::addNewMissionItem()
{
    MissionItemFactory factory(this);
    uint8_t seq = m_items.count();
    m_items.append(factory.create(seq == 0 ? MissionItem::Home : seq == 1 ?
                                                 MissionItem::Takeoff :
                                                 MissionItem::Waypoint));
    emit missionItemsChanged(m_items);
}

void Mission::removeMissionItem(MissionItem* item)
{
    this->take(m_items.indexOf(item));
    delete item;
}

void Mission::exchange(int first, int last)
{
    MissionItem* item = m_items[first];
    m_items[first] = m_items[last];
    m_items[last] = item;

    emit missionItemsChanged(m_items);
}
