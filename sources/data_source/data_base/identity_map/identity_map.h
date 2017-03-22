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

        MissionPtr mission(int id, bool reload = false);
        MissionItemPtr missionItem(int id, bool reload = false);
        VehiclePtr vehicle(int id, bool reload = false);

        bool saveMission(const MissionPtr& mission);
        bool saveMissionItem(const MissionItemPtr& missionItem);
        bool saveVehicle(const VehiclePtr& vehicle);

        bool removeMission(const MissionPtr& mission);
        bool removeMissionItem(const MissionItemPtr& missionItem);
        bool removeVehicle(const VehiclePtr& vehicle);

        void unloadMission(const MissionPtr& mission);
        void unloadMissionItem(const MissionItemPtr& missionItem);
        void unloadVehicle(const VehiclePtr& vehicle);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // IDENTITY_MAP_H
