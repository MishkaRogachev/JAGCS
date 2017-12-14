#ifndef MISSION_SERVICE_H
#define MISSION_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "dao_traits.h"
#include "mission_item.h"

namespace domain
{
    class MissionService: public QObject
    {
        Q_OBJECT

    public:
        explicit MissionService(QObject* parent = nullptr);
        ~MissionService() override;

        dao::MissionPtr mission(int id) const;
        dao::MissionItemPtr missionItem(int id) const;
        dao::MissionAssignmentPtr assignment(int id) const;

        dao::MissionAssignmentPtr missionAssignment(int missionId) const;
        dao::MissionAssignmentPtr vehicleAssignment(int vehicleId) const;

        dao::MissionItemPtrList missionItems(int missionId) const;
        dao::MissionItemPtr missionItem(int missionId, int sequence) const;

        dao::MissionPtrList missions() const;
        dao::MissionItemPtrList missionItems() const;
        dao::MissionAssignmentPtrList missionAssignments() const;

        dao::MissionItemPtr currentWaypoint(int vehicleId) const;
        dao::MissionItemPtr addNewMissionItem(int missionId,
                                              dao::MissionItem::Command command,
                                              int sequence);

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

        void fixMissionItemOrder(int missionId);

        void assign(int missionId, int vehicleId);
        void unassign(int missionId);

        void setCurrentItem(int vehicleId, const dao::MissionItemPtr& current);
        void swapItems(const dao::MissionItemPtr& first, const dao::MissionItemPtr& second);

    signals:
        void missionAdded(dao::MissionPtr mission);
        void missionRemoved(dao::MissionPtr mission);
        void missionChanged(dao::MissionPtr mission);

        void missionItemAdded(dao::MissionItemPtr item);
        void missionItemRemoved(dao::MissionItemPtr item);
        void missionItemChanged(dao::MissionItemPtr item);
        void currentItemChanged(int vehicleId, dao::MissionItemPtr item);

        void assignmentAdded(dao::MissionAssignmentPtr assignment);
        void assignmentRemoved(dao::MissionAssignmentPtr assignment);
        void assignmentChanged(dao::MissionAssignmentPtr assignment);

        void download(dao::MissionAssignmentPtr assignment);
        void upload(dao::MissionAssignmentPtr assignment);
        void cancelSync(dao::MissionAssignmentPtr assignment);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_SERVICE_H
