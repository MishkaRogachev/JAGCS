#ifndef DB_FACADE_H
#define DB_FACADE_H

// Qt
#include <QScopedPointer>

// Internal
#include "db_traits.h"

namespace db
{
    class DbFacade
    {
    public:
        DbFacade();
        ~DbFacade();

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

        LinkDescriptionPtrList loadLinks(const QString& condition = QString(),
                                         bool reload  = false);
        VehicleDescriptionPtrList loadVehicles(const QString& condition = QString(),
                                               bool reload  = false);
        MissionPtrList loadMissions(const QString& condition = QString(),
                                    bool reload  = false);
        MissionItemPtrList loadItems(const QString& condition = QString(),
                                     bool reload  = false);

        MissionAssignmentPtr missionAssignment(int missionId);
        MissionAssignmentPtr vehicleAssignment(int vehicleId);

        MissionItemPtrList missionItems(int missionId);
        MissionItemPtr missionItem(int missionId, int sequence);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DB_FACADE_H
