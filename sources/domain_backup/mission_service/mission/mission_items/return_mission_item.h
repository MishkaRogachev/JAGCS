#ifndef RETURN_MISSION_ITEM_H
#define RETURN_MISSION_ITEM_H

#include "abstract_mission_item.h"

namespace domain
{
    class ReturnMissionItem : public AbstractMissionItem
    {
        Q_OBJECT

    public:
        explicit ReturnMissionItem(Mission* mission);

        void clone(AbstractMissionItem* mission) override;
    };
}

#endif // RETURN_MISSION_ITEM_H
