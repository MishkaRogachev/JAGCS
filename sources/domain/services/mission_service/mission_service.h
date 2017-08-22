#ifndef MISSION_SERVICE_H
#define MISSION_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "dao_traits.h"

namespace domain
{
    class MissionService: public QObject
    {
        Q_OBJECT

    public:
        explicit MissionService(QObject* parent = nullptr);
        ~MissionService() override;

        dao::MissionPtr mission(int id, bool reload = false);
        dao::MissionItemPtr missionItem(int id, bool reload = false);
        dao::MissionAssignmentPtr assignment(int id, bool reload = false);

        dao::MissionAssignmentPtr missionAssignment(int missionId);
        dao::MissionAssignmentPtr vehicleAssignment(int vehicleId);

        dao::MissionItemPtrList missionItems(int missionId);
        dao::MissionItemPtr missionItem(int missionId, int sequence);

        dao::MissionPtrList missions(const QString& condition = QString(), bool reload  = false);
        dao::MissionItemPtrList missionItems(const QString& condition = QString(), bool reload  = false);

        dao::MissionItemPtr currentWaypoint(int vehicleId) const;
        bool isItemCurrent(const dao::MissionItemPtr& item) const;

    public slots:
        bool save(const dao::MissionPtr& mission);
        bool save(const dao::MissionItemPtr& item);
        bool save(const dao::MissionAssignmentPtr& assignment);

        bool remove(const dao::MissionPtr& mission);
        bool remove(const dao::MissionItemPtr& item);
        bool remove(const dao::MissionAssignmentPtr& assignment);

        void unload(const dao::MissionPtr& mission);
        void unload(const dao::MissionItemPtr& item);
        void unload(const dao::MissionAssignmentPtr& assignment);

        void addNewMissionItem(int missionId);
        void saveMissionItems(int missionId);
        void fixMissionItemOrder(int missionId);

        void assign(int missionId, int vehicleId);
        void unassign(int missionId);

        void setCurrentItem(int vehicleId, const dao::MissionItemPtr& item);

    signals:
        void missionAdded(dao::MissionPtr mission);
        void missionRemoved(dao::MissionPtr mission);
        void missionChanged(dao::MissionPtr mission);

        void missionItemAdded(dao::MissionItemPtr item);
        void missionItemRemoved(dao::MissionItemPtr item);
        void missionItemChanged(dao::MissionItemPtr item);

        void assignmentAdded(dao::MissionAssignmentPtr assignment);
        void assignmentRemoved(dao::MissionAssignmentPtr assignment);
        void assignmentChanged(dao::MissionAssignmentPtr assignment);

        void download(dao::MissionAssignmentPtr assignment);
        void upload(dao::MissionAssignmentPtr assignment);
        void cancelSync(dao::MissionAssignmentPtr assignment);

        void selectCurrentItem(int vehicleId, int item);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_SERVICE_H
