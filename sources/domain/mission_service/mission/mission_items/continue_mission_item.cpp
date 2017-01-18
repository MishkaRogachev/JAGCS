#include "continue_mission_item.h"

using namespace domain;

ContinueMissionItem::ContinueMissionItem(Mission* mission):
    AltitudeMissionItem(mission, Continue, true)
{}
