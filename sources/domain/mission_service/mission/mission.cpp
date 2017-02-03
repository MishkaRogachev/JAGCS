#include "mission.h"

// Qt
#include <QDebug>

// Internal
#include "mission_vehicle.h"
#include "mission_item_factory.h"
#include "altitude_mission_item.h"

using namespace domain;

Mission::Mission(QObject* parent):
    QObject(parent),
    m_assignment(new MissionVehicle(this))
{}

Mission::~Mission()
{
    while (!m_items.isEmpty())
    {
        delete m_items.takeLast();
    }
    emit missionItemsChanged(m_items);
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
    emit missionItemsChanged(m_items);
    return item;
}

MissionVehicle* Mission::assignment() const
{
    return m_assignment;
}

Vehicle* Mission::assignedVehicle() const
{
    return m_assignment->vehicle();
}

void Mission::setCount(int count)
{
    while (m_items.count() < count)
    {
        m_items.append(nullptr);
    }

    while (m_items.count() > count)
    {
        delete m_items.takeLast();
    }

    emit missionItemsChanged(m_items);
}

void Mission::setMissionItem(int seq, MissionItem* item)
{
    if (seq >= m_items.count())
    {
        this->setCount(seq + 1);
    }

    MissionItem* oldItem = m_items[seq];

    m_items[seq] = item;
    emit missionItemsChanged(m_items);

    if (oldItem) delete oldItem;
}

void Mission::addNewMissionItem()
{
    MissionItemFactory factory(this);
    uint8_t seq = m_items.count();
    m_items.append(factory.create(seq == 0 ? MissionItem::Home : seq == 1 ?
                                                 MissionItem::Takeoff :
                                                 MissionItem::Waypoint));
    AltitudeMissionItem* item = qobject_cast<AltitudeMissionItem*>(m_items.last());
    if (item)
    {
        item->setAltitude(-1 * item->climb());
    }

    emit missionItemsChanged(m_items);
}

void Mission::removeMissionItem(MissionItem* item)
{
    this->take(m_items.indexOf(item));
    delete item;
}

void Mission::exchange(int first, int last)
{
    MissionItem* item = m_items[first];
    m_items[first] = m_items[last];
    m_items[last] = item;

    if (first == 0 || last == 0)
    {
        MissionItem::Command command = m_items[first]->command();
        m_items[first]->replaceWithCommand(m_items[last]->command());
        m_items[last]->replaceWithCommand(command);
    }

    emit missionItemsChanged(m_items);
}

void Mission::unassignVehicle()
{
    this->assignVehicle(nullptr);
}

void Mission::assignVehicle(Vehicle* vehicle)
{
    if (m_assignment->vehicle() == vehicle) return;

    m_assignment->setVehicle(vehicle);

    if (vehicle) emit assigned(vehicle);
    else emit unassigned();
}
