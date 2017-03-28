#ifndef LANDING_MISSION_ITEM_H
#define LANDING_MISSION_ITEM_H

#include "position_mission_item.h"

namespace domain
{
    class LandingMissionItem: public PositionMissionItem
    {
        Q_OBJECT

    public:
        explicit LandingMissionItem(Mission* mission);
    };
}

#endif // LANDING_MISSION_ITEM_H
