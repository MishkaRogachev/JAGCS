#ifndef IDENTITY_MAP_H
#define IDENTITY_MAP_H

#include "identity_traits.h"

namespace data_source
{
    class IdentityMap // TODO: replace with T-specific IdentityMap and one domain manager
    {
    public:
        IdentityMap();
        ~IdentityMap();

        MissionPtr readMission(int id, bool reload = false);
        MissionItemPtr readMissionItem(int id, bool reload = false);
        VehiclePtr readVehicle(int id, bool reload = false);
        MissionAssignmentPtr readAssignment(int id, bool reload = false);

        bool save(const MissionPtr& mission);
        bool save(const MissionItemPtr& missionItem);
        bool save(const VehiclePtr& vehicle);
        bool save(const MissionAssignmentPtr& assignment);

        bool remove(const MissionPtr& mission);
        bool remove(const MissionItemPtr& missionItem);
        bool remove(const VehiclePtr& vehicle);
        bool remove(const MissionAssignmentPtr& assignment);

        void unload(const MissionPtr& mission);
        void unload(const MissionItemPtr& missionItem);
        void unload(const VehiclePtr& vehicle);
        void unload(const MissionAssignmentPtr& assignment);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // IDENTITY_MAP_H
