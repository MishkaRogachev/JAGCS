#ifndef MISSION_SERVICE_H
#define MISSION_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "dto_traits.h"
#include "mission_item.h"

namespace domain
{
    class MissionService: public QObject
    {
        Q_OBJECT

    public:
        explicit MissionService(QObject* parent = nullptr);
        ~MissionService() override;

        dto::MissionPtr mission(int id) const;
        dto::MissionItemPtr missionItem(int id) const;
        dto::MissionAssignmentPtr assignment(int id) const;

        dto::MissionAssignmentPtr missionAssignment(int missionId) const;
        dto::MissionAssignmentPtr vehicleAssignment(int vehicleId) const;

        dto::MissionItemPtrList missionItems(int missionId) const;
        dto::MissionItemPtr missionItem(int missionId, int sequence) const;

        dto::MissionPtrList missions() const;
        dto::MissionItemPtrList missionItems() const;
        dto::MissionAssignmentPtrList missionAssignments() const;

        dto::MissionItemPtr currentWaypoint(int vehicleId) const;
        dto::MissionItemPtr addNewMissionItem(int missionId,
                                              dto::MissionItem::Command command,
                                              int sequence);
        void addNewMission(const QString& name);

    public slots:
        bool save(const dto::MissionPtr& mission);
        bool save(const dto::MissionItemPtr& item);
        bool save(const dto::MissionAssignmentPtr& assignment);

        bool remove(const dto::MissionPtr& mission);
        bool remove(const dto::MissionItemPtr& item);
        bool remove(const dto::MissionAssignmentPtr& assignment);

        void unload(const dto::MissionPtr& mission);
        void unload(const dto::MissionItemPtr& item);
        void unload(const dto::MissionAssignmentPtr& assignment);

        void fixMissionItemOrder(int missionId);
        void fixMissionItemCount(int missionId);

        void assign(int missionId, int vehicleId);
        void unassign(int missionId);

        void setCurrentItem(int vehicleId, const dto::MissionItemPtr& current);
        void swapItems(const dto::MissionItemPtr& first, const dto::MissionItemPtr& second);

        void onVehicleChanged(const dto::VehiclePtr& vehicle);

    signals:
        void missionAdded(dto::MissionPtr mission);
        void missionRemoved(dto::MissionPtr mission);
        void missionChanged(dto::MissionPtr mission);

        void missionItemAdded(dto::MissionItemPtr item);
        void missionItemRemoved(dto::MissionItemPtr item);
        void missionItemChanged(dto::MissionItemPtr item);
        void currentItemChanged(int vehicleId, dto::MissionItemPtr item);

        void assignmentAdded(dto::MissionAssignmentPtr assignment);
        void assignmentRemoved(dto::MissionAssignmentPtr assignment);
        void assignmentChanged(dto::MissionAssignmentPtr assignment);

        void download(dto::MissionAssignmentPtr assignment);
        void upload(dto::MissionAssignmentPtr assignment);
        void cancelSync(dto::MissionAssignmentPtr assignment);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_SERVICE_H
