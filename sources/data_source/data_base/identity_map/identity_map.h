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

        MissionPtr readMission(int id, bool reload = false);
        MissionItemPtr readMissionItem(int id, bool reload = false);
        VehiclePtr readVehicle(int id, bool reload = false);

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
