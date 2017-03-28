#ifndef MISSION_ITEM_FACTORY_H
#define MISSION_ITEM_FACTORY_H

#include "abstract_mission_item.h"

namespace domain
{
    class MissionItemFactory
    {
    public:
        MissionItemFactory(Mission* mision);

        AbstractMissionItem* create(Command command);

    private:
        Mission* m_mision;
    };
}

#endif // MISSION_ITEM_FACTORY_H
