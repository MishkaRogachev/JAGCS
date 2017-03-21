#include "mission.h"

// Internal
#include "identity_map.h"
#include "mission_item.h"

using namespace data_source;

Mission::Mission(IdentityMap* iMap):
    BaseEntity(iMap)
{}

QString Mission::tableName()
{
    return "missions";
}

QString Mission::name() const
{
    return m_name;
}

void Mission::setName(const QString& name)
{
    m_name = name;
}

int Mission::count() const
{
    return m_items.count();
}

const MissionItemPtrList& Mission::items() const
{
    return m_items;
}

MissionItemPtrList&Mission::items()
{
    return m_items;
}

MissionItemPtr Mission::item(int index) const
{
    return m_items.at(index);
}

void Mission::addItem(const MissionItemPtr& item)
{
    m_items.append(item);
}

MissionItemPtr Mission::takeItem(int index)
{
    MissionItemPtr item = m_items.takeAt(index);
    item->setMission(MissionPtr());
    this->fixSequenceOrder();
    return item;
}

void Mission::insertItem(int index, const MissionItemPtr& item)
{
    m_items.insert(index, item);
    item->setMission(m_iMap->mission(this->id()));
    this->fixSequenceOrder();
}

void Mission::fixSequenceOrder()
{
    for (int seq = 0; seq < m_items.count(); ++seq)
    {
        m_items[seq]->setSequence(seq);
    }
}
