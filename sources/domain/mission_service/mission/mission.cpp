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
    emit missionItemRemoved(item);
    return item;
}

void Mission::setCount(int count)
{
    while (m_items.count() < count)
    {
        m_items.append(nullptr);
        emit missionItemAdded(nullptr);
    }

    while (m_items.count() > count)
    {
        MissionItem* item = m_items.takeLast();
        emit missionItemRemoved(item);
        delete item;
    }
}

void Mission::setMissionItem(int seq, MissionItem* item)
{
    if (seq >= m_items.count())
    {
        this->setCount(seq + 1);
    }

    emit missionItemRemoved(m_items[seq]);
    if (m_items[seq]) delete m_items[seq];

    m_items[seq] = item;
    emit missionItemAdded(item);
}

void Mission::addNewMissionItem()
{
    MissionItemFactory factory(this);
    uint8_t seq = m_items.count();
    m_items.append(factory.create(seq == 0 ? MissionItem::Home : seq == 1 ?
                                                 MissionItem::Takeoff :
                                                 MissionItem::Waypoint));
    emit missionItemAdded(m_items[seq]);
}

void Mission::deleteMissionItem(MissionItem* item) // FIXME: update sequence after remove
{
    this->take(m_items.indexOf(item));
    delete item;
}

void Mission::exchange(int first, int last)
{
    MissionItem* firstItem = m_items[first];
    m_items[first] = nullptr;
    emit missionItemRemoved(firstItem);

    MissionItem* lastItem = m_items[last];
    m_items[last] = nullptr;
    emit missionItemRemoved(lastItem);

    m_items[first] = lastItem;
    emit missionItemAdded(lastItem);

    m_items[last] = firstItem;
    emit missionItemAdded(firstItem);
}
