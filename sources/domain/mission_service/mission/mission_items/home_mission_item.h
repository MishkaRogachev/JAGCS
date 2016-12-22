#ifndef HOME_MISSION_ITEM_H
#define HOME_MISSION_ITEM_H

#include "position_mission_item.h"

namespace domain
{
    class HomeMissionitem: public PositionMissionItem
    {
        Q_OBJECT

    public:
        HomeMissionitem(Mission* mission);
    };
}

#endif // HOME_MISSION_ITEM_H
