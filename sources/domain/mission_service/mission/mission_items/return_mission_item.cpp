#include "return_mission_item.h"

using namespace domain;

ReturnMissionItem::ReturnMissionItem(Mission* mission):
    MissionItem(mission, Return)
{}
