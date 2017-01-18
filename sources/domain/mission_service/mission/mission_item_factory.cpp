#include "mission_item_factory.h"

// QT
#include <QDebug>

// Internal
#include "settings_provider.h"
#include "settings.h"

#include "mission.h"

#include "home_mission_item.h"
#include "takeoff_mission_item.h"
#include "waypoint_mission_item.h"
#include "loiter_mission_item.h"
#include "continue_mission_item.h"
#include "return_mission_item.h"
#include "landing_mission_item.h"

using namespace domain;

MissionItemFactory::MissionItemFactory(Mission* mision):
    m_mision(mision)
{}

MissionItem* MissionItemFactory::create(MissionItem::Command command)
{
    switch (command) {
    case MissionItem::Home:
        return new HomeMissionitem(m_mision);
    case MissionItem::Takeoff:
        return new TakeoffMissionItem(m_mision, SettingsProvider::value(
                          mission_settings::defaultTakeoffPitch).toFloat());
    case MissionItem::Waypoint:
        return new WaypointMissionItem(m_mision, SettingsProvider::value(
                      mission_settings::defaultAcceptanceRadius).toFloat());
    case MissionItem::Loiter:
        return new LoiterMissionItem(m_mision);
    case MissionItem::Continue:
        return new ContinueMissionItem(m_mision);
    case MissionItem::Return:
        return new ReturnMissionItem(m_mision);
    case MissionItem::Landing:
        return new LandingMissionItem(m_mision);
    default:
        return nullptr;
    }
}
