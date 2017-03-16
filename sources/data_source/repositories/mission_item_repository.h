#ifndef MISSION_ITEM_REPOSITORY_H
#define MISSION_ITEM_REPOSITORY_H

// Internal
#include "generic_repository.h"
#include "generic_repository_impl.h"
#include "mission_item.h"

namespace data_source
{
    class MissionItemRepository: public GenericRepository<MissionItem>
    {
    public:
        MissionItemRepository();
    };
}

#endif // MISSION_ITEM_REPOSITORY_H
