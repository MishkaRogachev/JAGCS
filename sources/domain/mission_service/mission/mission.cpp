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

MissionItem* Mission::item(unsigned seq) const
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
    while (m_missionItems.count() > seq)
    {
        m_missionItems.append(nullptr);
    }

    if (!m_missionItems.at(seq))
    {
        m_missionItems[seq] = new MissionItem(this);
        emit missionItemAdded(m_missionItems[seq]);
    }

    return m_missionItems.at(seq);
}

void Mission::reserve(unsigned count)
{
    m_missionItems.reserve(count);
}

void Mission::addNewMissionItem()
{
    m_missionItems.append(new domain::MissionItem(this));
    emit missionItemAdded(m_missionItems.last());
}

void Mission::removeMissionItem(MissionItem* item)
{
    m_missionItems.removeOne(item);
    emit missionItemRemoved(item);
    delete item;
}
