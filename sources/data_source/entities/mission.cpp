#include "mission.h"

// Internal
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

const MissionItemPtrList& Mission::items() const
{
    return m_items;
}

MissionItemPtr Mission::item(int index) const
{
    return m_items.at(index);
}

void Mission::addItem(MissionItemPtr item)
{
    m_items.append(item);
}

void Mission::removeItem(int index)
{
    m_items.removeAt(index);
}
