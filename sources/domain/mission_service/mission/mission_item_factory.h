#ifndef MISSION_ITEM_FACTORY_H
#define MISSION_ITEM_FACTORY_H

#include "mission_item.h"

namespace domain
{
    class MissionItemFactory
    {
    public:
        MissionItemFactory(Mission* mision);

        MissionItem* create(Command command);

    private:
        Mission* m_mision;
    };
}

#endif // MISSION_ITEM_FACTORY_H
