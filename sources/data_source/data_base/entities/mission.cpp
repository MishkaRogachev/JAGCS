#include "mission.h"

// Internal
#include "identity_map.h"
#include "mission_item.h"

using namespace data_source;

Mission::Mission(int id):
    BaseEntity(id)
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

void Mission::appendItem(const MissionItemPtr& item)
{
    item->setSequence(this->count());
    item->setMissionId(this->id());
    m_items.append(item);
}

MissionItemPtr Mission::takeItem(int index)
{
    MissionItemPtr item = m_items.takeAt(index);
    item->setSequence(-1);
    item->setMissionId(this->id());
    this->fixSequenceOrder();
    return item;
}

MissionItemPtr Mission::takeLast()
{
    MissionItemPtr item = m_items.takeLast();
    item->setSequence(-1);
    item->setMissionId(this->id());
    return item;
}

void Mission::insertItem(int index, const MissionItemPtr& item)
{
    m_items.insert(index, item);
    item->setMissionId(this->id());
    this->fixSequenceOrder();
}

void Mission::setItem(int index, const MissionItemPtr& item)
{
    if (index < m_items.count())
    {
        this->takeItem(index);
        this->insertItem(index, item);
        return;
    }

    while (index > m_items.count()) this->appendItem(MissionItemPtr::create());
    this->appendItem(item);
}

void Mission::exchangePosition(int first, int last)
{
    if (first > last) return this->exchangePosition(last, first);

    MissionItemPtr lastItem = m_items.takeAt(last);
    MissionItemPtr firstItem = m_items.takeAt(first);

    m_items.insert(first, lastItem);
    m_items.insert(last, firstItem);

    this->fixSequenceOrder();
}

void Mission::moveUp(int index)
{
    this->exchangePosition(index, index + 1);
}

void Mission::moveDown(int index)
{
    this->exchangePosition(index, index - 1);
}

void Mission::fixSequenceOrder()
{
    for (int seq = 0; seq < m_items.count(); ++seq)
    {
        m_items[seq]->setSequence(seq);
    }
}

void Mission::setCount(int count)
{
    while (m_items.count() > count) this->takeLast();
    if (m_items.count() < count) m_items.reserve(count);
}
