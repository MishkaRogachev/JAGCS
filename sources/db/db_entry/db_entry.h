#ifndef DB_ENTRY_H
#define DB_ENTRY_H

// Qt
#include <QScopedPointer>

// Internal
#include "db_traits.h"

namespace db
{
    class DbEntry // TODO: db facade
    {
    public:
        DbEntry();
        ~DbEntry();

        MissionPtr readMission(int id, bool reload = false);
        MissionItemPtr readMissionItem(int id, bool reload = false);
        VehicleDescriptionPtr readVehicle(int id, bool reload = false);
        LinkDescriptionPtr readLink(int id, bool reload = false);
        MissionAssignmentPtr readAssignment(int id, bool reload = false);

        bool save(const MissionPtr& mission);
        bool save(const MissionItemPtr& missionItem);
        bool save(const VehicleDescriptionPtr& vehicle);
        bool save(const LinkDescriptionPtr& link);
        bool save(const MissionAssignmentPtr& assignment);

        bool remove(const MissionPtr& mission);
        bool remove(const MissionItemPtr& missionItem);
        bool remove(const VehicleDescriptionPtr& vehicle);
        bool remove(const LinkDescriptionPtr& link);
        bool remove(const MissionAssignmentPtr& assignment);

        LinkDescriptionPtrList loadLinks();
        VehicleDescriptionPtrList loadVehicles();
        MissionPtrList loadMissions();

        MissionAssignmentPtr missionAssignment(int missionId);
        MissionAssignmentPtr vehicleAssignment(int vehicleId);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DB_ENTRY_H
