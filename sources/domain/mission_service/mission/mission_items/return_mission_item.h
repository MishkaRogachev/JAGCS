#ifndef RETURN_MISSION_ITEM_H
#define RETURN_MISSION_ITEM_H

#include "mission_item.h"

namespace domain
{
    class ReturnMissionItem : public MissionItem
    {
        Q_OBJECT

    public:
        explicit ReturnMissionItem(Mission* mission);
    };
}

#endif // RETURN_MISSION_ITEM_H
