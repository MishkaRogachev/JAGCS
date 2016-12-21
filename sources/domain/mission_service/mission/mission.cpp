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

MissionItem* Mission::requestItem(int seq)
{
    if (seq >= m_items.count())
    {
        this->setCount(seq + 1);
    }

    return m_items.at(seq);
}

void Mission::setCount(int count)
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
    m_items.append(m_itemFactory.create());
    emit missionItemAdded(m_items.last());
}

void Mission::removeMissionItem(MissionItem* item)
{
    m_items.removeOne(item);
    emit missionItemRemoved(item);
    delete item;
}
