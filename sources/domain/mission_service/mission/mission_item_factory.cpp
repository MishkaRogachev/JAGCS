#include "mission_item_factory.h"

// QT
#include <QDebug>

// Internal
#include "mission.h"

using namespace domain;

MissionItemFactory::MissionItemFactory(Mission* mision):
    m_mision(mision)
{}

MissionItem* MissionItemFactory::create()
{
    return new MissionItem(m_mision,
                           m_mision->items().empty() ?
                               MissionItem::Home : MissionItem::Waypoint,
                           qQNaN(), qQNaN(), 0, !m_mision->items().empty(),
                           qQNaN(), qQNaN(), 0);
}
