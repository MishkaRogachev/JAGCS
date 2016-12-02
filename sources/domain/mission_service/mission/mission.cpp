#include "mission.h"

using namespace domain;

Mission::Mission(QObject* parent):
    QObject(parent)
{}

int Mission::count() const
{
    return m_missionItems.count();
}

void Mission::setCount(unsigned count)
{
    for (unsigned i = 0; i < count; ++i)
    {
        if (m_missionItems.contains(i)) continue;
        m_missionItems[i] = nullptr;
    }
}

void Mission::setMissionItem(unsigned seq, MissionItem* item)
{
    if (m_missionItems.value(seq, nullptr))
        this->removeMissionItem(seq);

    m_missionItems[seq] = item;
    emit missionItemAdded(seq);
}

void Mission::removeMissionItem(unsigned seq)
{
    MissionItem* item = m_missionItems.take(seq);
    if (item) delete item;

    emit missionItemRemoved(seq);
}
