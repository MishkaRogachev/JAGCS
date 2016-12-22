#include "home_mission_item.h"

using namespace domain;

HomeMissionitem::HomeMissionitem(Mission* mission):
    PositionMissionItem(mission, Home, false)
{}
