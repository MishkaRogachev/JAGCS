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
        this->deleteMissionItem(m_items.first());
}

int Mission::count() const
{
    return m_items.count();
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

MissionItem* Mission::take(int seq)
{
    MissionItem* item = m_items.take(seq);
    emit missionItemRemoved(item);
    return item;
}

void Mission::setMissionItem(int seq, MissionItem* item)
{
    if (m_items.contains(seq))
    {
        this->deleteMissionItem(m_items[seq]);
    }

    m_items[seq] = item;
    emit missionItemAdded(item);
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

void Mission::deleteMissionItem(MissionItem* item) // FIXME: update sequence after remove
{
    this->take(m_items.key(item));
    delete item;
}

void Mission::exchange(int first, int last)
{
    if (!m_items.contains(first) || !m_items.contains(last)) return;

    MissionItem* firstItem = this->take(first);
    MissionItem* lastItem = this->take(last);
    this->setMissionItem(first, lastItem);
    this->setMissionItem(last, firstItem);
}
