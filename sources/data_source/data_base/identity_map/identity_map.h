#ifndef IDENTITY_MAP_H
#define IDENTITY_MAP_H

// Qt
#include <QScopedPointer>

// Internal
#include "identity_traits.h"

namespace data_source
{
    class IdentityMap // TODO: replace with ORM library
    {
    public:
        IdentityMap();
        ~IdentityMap();

        MissionPtr readMission(int id, bool reload = false);
        MissionItemPtr readMissionItem(int id, bool reload = false);
        VehiclePtr readVehicle(int id, bool reload = false);

        bool save(const MissionPtr& mission);
        bool save(const MissionItemPtr& missionItem);
        bool save(const VehiclePtr& vehicle);

        bool remove(const MissionPtr& mission);
        bool remove(const MissionItemPtr& missionItem);
        bool remove(const VehiclePtr& vehicle);

        void unload(const MissionPtr& mission);
        void unload(const MissionItemPtr& missionItem);
        void unload(const VehiclePtr& vehicle);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // IDENTITY_MAP_H
