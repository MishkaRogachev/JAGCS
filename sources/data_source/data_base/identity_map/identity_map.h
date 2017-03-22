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
        VehiclePtr vehicle(int id);

        MissionPtr createMission();
        MissionItemPtr createMissionItem(const MissionPtr& mission);
        VehiclePtr createVehicle();

        void saveMission(const MissionPtr& mission);
        void saveMissionAll(const MissionPtr& mission);
        void saveMissionItem(const MissionItemPtr& missionItem);
        void saveVehicle(const VehiclePtr& vehicle);

        void removeMission(const MissionPtr& mission);
        void removeMissionItem(const MissionItemPtr& missionItem);
        void removeVehicle(const VehiclePtr& vehicle);

        void unloadMission(const MissionPtr& mission);
        void unloadMissionItem(const MissionItemPtr& missionItem);
        void unloadVehicle(const VehiclePtr& vehicle);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // IDENTITY_MAP_H
