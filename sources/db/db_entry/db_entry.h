#ifndef DB_ENTRY_H
#define DB_ENTRY_H

// Qt
#include <QScopedPointer>

// Internal
#include "db_traits.h"

namespace db
{
    class DbEntry // TODO: facade interface(missions, itemsForMission etc)
    {
    public:
        DbEntry();
        ~DbEntry();

        MissionPtr readMission(int id, bool reload = false);
        MissionItemPtr readMissionItem(int id, bool reload = false);
        VehicleDescriptionPtr readVehicle(int id, bool reload = false);
        LinkDescriptionPtr readLink(int id, bool reload = false);

        bool save(const MissionPtr& mission);
        bool save(const MissionItemPtr& missionItem);
        bool save(const VehicleDescriptionPtr& vehicle);
        bool save(const LinkDescriptionPtr& link);

        bool remove(const MissionPtr& mission);
        bool remove(const MissionItemPtr& missionItem);
        bool remove(const VehicleDescriptionPtr& vehicle);
        bool remove(const LinkDescriptionPtr& link);

        void unload(const MissionPtr& mission);
        void unload(const MissionItemPtr& missionItem);
        void unload(const VehicleDescriptionPtr& vehicle);
        void unload(const LinkDescriptionPtr& link);

        LinkDescriptionPtrList loadLinks();
        VehicleDescriptionPtrList loadVehicles();
        MissionPtrList loadMissions();

        // TODO: db and services segregation of duties
        MissionAssignmentPtr missionAssignment(const MissionPtr& mission);
        MissionAssignmentPtr vehicleAssignment(const VehicleDescriptionPtr& vehicle);
        void assign(const MissionPtr& mission, const VehicleDescriptionPtr& vehicle);
        void unassign(const MissionPtr& mission);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DB_ENTRY_H
