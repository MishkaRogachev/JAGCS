#ifndef MISSION_REPOSITORY_H
#define MISSION_REPOSITORY_H

// Internal
#include "generic_repository.h"
#include "generic_repository_impl.h"
#include "mission.h"

namespace data_source
{
    class MissionRepository: public GenericRepository<Mission>
    {
    public:
        MissionRepository();
    };
}

#endif // MISSION_REPOSITORY_H
