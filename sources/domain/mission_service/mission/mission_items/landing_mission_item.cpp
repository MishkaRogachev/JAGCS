#include "landing_mission_item.h"

using namespace domain;

LandingMissionItem::LandingMissionItem(Mission* mission):
    DirectionMissionItem(mission, Landing, true)
{}
