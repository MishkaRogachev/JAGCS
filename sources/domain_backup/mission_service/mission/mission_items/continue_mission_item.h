#ifndef CONTINUE_MISSION_ITEM_H
#define CONTINUE_MISSION_ITEM_H

#include "altitude_mission_item.h"

namespace domain
{
    class ContinueMissionItem: public AltitudeMissionItem
    {
        Q_OBJECT

    public:
        explicit ContinueMissionItem(Mission* mission);
    };
}

#endif // CONTINUE_MISSION_ITEM_H
