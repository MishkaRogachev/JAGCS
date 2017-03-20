#ifndef IDENTITY_MAP_H
#define IDENTITY_MAP_H

#include "identity_traits.h"

namespace data_source
{
    class IdentityMap
    {
    public:
        IdentityMap();
        ~IdentityMap();

        MissionPtr mission(int id);
        MissionItemPtr missionItem(int id);

        MissionPtr createMission();
        MissionItemPtr createItemForMission(const MissionPtr& mission);

        void saveMission(const MissionPtr& mission);
        void saveMissionAll(const MissionPtr& mission);
        void saveMissionItem(const MissionItemPtr& missionItem);

        void removeMission(const MissionPtr& mission);
        void removeMissionItem(const MissionItemPtr& missionItem);

        void unloadMission(const MissionPtr& mission);
        void unloadMissionItem(const MissionItemPtr& missionItem);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // IDENTITY_MAP_H
