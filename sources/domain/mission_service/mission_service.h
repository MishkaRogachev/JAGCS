#ifndef MISSION_SERVICE_H
#define MISSION_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

namespace db
{
    class DbFacade;
}

namespace domain
{
    class MissionService: public QObject
    {
        Q_OBJECT

    public:
        explicit MissionService(db::DbFacade* facade, QObject* parent = nullptr);
        ~MissionService() override;

        db::MissionPtrList missions() const;

        db::MissionPtr missionByName(const QString& name) const;
        db::MissionPtr missionByVehicle(const db::VehicleDescriptionPtr& vehicle) const;

        db::MissionAssignmentPtr missionAssignment(const db::MissionPtr& mission) const;
        void assign(const db::MissionPtr& mission, const db::VehicleDescriptionPtr& vehicle);
        void unassign(const db::MissionPtr& mission);

        db::MissionItemPtrList missionItems() const;
        db::MissionItemPtrList missionItems(const db::MissionPtr& mission) const;
        db::MissionItemPtr missionItem(const db::MissionPtr& mission,
                                       int sequence) const;

    public slots:
        void saveMission(const db::MissionPtr& mission);
        void removeMission(const db::MissionPtr& mission);

        void saveMissionItem(const db::MissionItemPtr& item);
        void removeMissionItem(const db::MissionItemPtr& item);
        void addNewMissionItem(const db::MissionPtr& mission);
        void saveMissionItems(const db::MissionPtr& mission);

        void fixSequenceOrder(int missionId);

    signals:
        void missionAdded(const db::MissionPtr& mission);
        void missionRemoved(const db::MissionPtr& mission);
        void missionChanged(const db::MissionPtr& mission);

        void assignmentAdded(const db::MissionAssignmentPtr& missionAssignment);
        void assignmentRemoved(const db::MissionAssignmentPtr& missionAssignment);
        void assignmentChanged(const db::MissionAssignmentPtr& missionAssignment);

        void missionItemAdded(const db::MissionItemPtr& item);
        void missionItemRemoved(const db::MissionItemPtr& item);
        void missionItemChanged(const db::MissionItemPtr& item);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_SERVICE_H
