#include "mission.h"

// Qt
#include <QDebug>

using namespace domain;

Mission::Mission(QObject* parent):
    QObject(parent)
{}

int Mission::count() const
{
    return m_missionItems.count();
}

MissionItem* Mission::item(int seq) const
{
    return m_missionItems.value(seq, nullptr);
}

const QList<MissionItem*>& Mission::items() const
{
    return m_missionItems;
}

int Mission::sequence(MissionItem* item) const
{
    return m_missionItems.indexOf(item);
}

MissionItem* Mission::requestItem(int seq)
{
    if (seq >= m_missionItems.count())
    {
        this->setCount(seq + 1);
    }

    return m_missionItems.at(seq);
}

void Mission::setCount(int count)
{
    while (count > m_missionItems.count())
    {
        this->addNewMissionItem();
    }

    while (count < m_missionItems.count())
    {
        this->removeMissionItem(m_missionItems.last());
    }
}

void Mission::addNewMissionItem()
{
    m_missionItems.append(new MissionItem(m_missionItems.empty() ?
                          MissionItem::Takeoff : MissionItem::Waypoint, this));
    emit missionItemAdded(m_missionItems.last());
}

void Mission::removeMissionItem(MissionItem* item)
{
    m_missionItems.removeOne(item);
    emit missionItemRemoved(item);
    delete item;
}
