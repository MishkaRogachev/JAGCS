#include "mission.h"

// Qt
#include <QDebug>

// Internal
#include "mission_item_factory.h"

using namespace domain;

Mission::Mission(QObject* parent):
    QObject(parent),
    m_totalCount(-1)
{}

Mission::~Mission()
{
    while (!m_items.isEmpty())
        this->removeMissionItem(m_items.first());
}

int Mission::count() const
{
    return m_items.count();
}

int Mission::totalCount() const
{
    return m_totalCount;
}

MissionItem* Mission::item(int seq) const
{
    return m_items.value(seq, nullptr);
}

QList<MissionItem*> Mission::items() const
{
    return m_items.values();
}

int Mission::sequence(MissionItem* item) const
{
    return m_items.key(item);
}

void Mission::setMissionItem(int seq, MissionItem* item)
{
    if (m_items.contains(seq))
    {
        this->removeMissionItem(m_items[seq]);
    }

    m_items[seq] = item;
    emit missionItemAdded(item);
}

void Mission::setTotalCount(int totalCount)
{
    if (m_totalCount == totalCount) return;

    m_totalCount = totalCount;
    emit totalCountChanged(totalCount);
}

void Mission::addNewMissionItem()
{
    MissionItemFactory factory(this);
    uint8_t seq = m_items.empty() ? 0 : m_items.keys().last() + 1;
    m_items[seq] = factory.create(seq == 0 ? MissionItem::Home : seq == 1 ?
                                                 MissionItem::Takeoff :
                                                 MissionItem::Waypoint);
    emit missionItemAdded(m_items[seq]);
}

void Mission::removeMissionItem(MissionItem* item)
{
    m_items.take(m_items.key(item));
    emit missionItemRemoved(item);
    delete item;
}
