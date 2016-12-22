#ifndef LANDING_MISSION_ITEM_H
#define LANDING_MISSION_ITEM_H

#include "direction_mission_item.h"

namespace domain
{
    class LandingMissionItem: public DirectionMissionItem
    {
        Q_OBJECT

    public:
        explicit LandingMissionItem(Mission* mission);
    };
}

#endif // LANDING_MISSION_ITEM_H
