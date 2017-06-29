#ifndef DB_FACADE_H
#define DB_FACADE_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

namespace db
{
    // TODO: work with db in separated thread
    class DbFacade: public QObject
    {
        Q_OBJECT

    public:
        explicit DbFacade(QObject* parent = nullptr);
        ~DbFacade() override;

        MissionPtr mission(int id, bool reload = false);
        MissionItemPtr missionItem(int id, bool reload = false);
        MissionAssignmentPtr assignment(int id, bool reload = false);
        VehiclePtr vehicle(int id, bool reload = false);
        LinkDescriptionPtr link(int id, bool reload = false);
        VideoSourcePtr videoSource(int id, bool reload = false);

        bool save(const MissionPtr& mission);
        bool save(const MissionItemPtr& item);
        bool save(const MissionAssignmentPtr& assignment);
        bool save(const VehiclePtr& vehicle);
        bool save(const LinkDescriptionPtr& link);
        bool save(const VideoSourcePtr& videoSource);

        bool remove(const MissionPtr& mission);
        bool remove(const MissionItemPtr& item);
        bool remove(const MissionAssignmentPtr& assignment);
        bool remove(const VehiclePtr& vehicle);
        bool remove(const LinkDescriptionPtr& link);

        LinkDescriptionPtrList links(const QString& condition = QString(), bool reload  = false);
        VehiclePtrList vehicles(const QString& condition = QString(), bool reload  = false);
        MissionPtrList missions(const QString& condition = QString(), bool reload  = false);
        MissionItemPtrList missionItems(const QString& condition = QString(), bool reload  = false);
        VideoSourcePtrList videoSources(const QString& condition = QString(), bool reload  = false);

        MissionAssignmentPtr missionAssignment(int missionId);
        MissionAssignmentPtr vehicleAssignment(int vehicleId);

        MissionItemPtrList missionItems(int missionId);
        MissionItemPtr missionItem(int missionId, int sequence);

        int vehicleIdByMavId(int mavId) const;

    public slots:
        void addNewMissionItem(int missionId);
        void saveMissionItems(int missionId);
        void fixMissionItemOrder(int missionId);

        void assign(int missionId, int vehicleId);
        void unassign(int missionId);

    signals:
        void missionAdded(db::MissionPtr mission);
        void missionRemoved(db::MissionPtr mission);
        void missionChanged(db::MissionPtr mission);

        void missionItemAdded(db::MissionItemPtr item);
        void missionItemRemoved(db::MissionItemPtr item);
        void missionItemChanged(db::MissionItemPtr item);

        void assignmentAdded(db::MissionAssignmentPtr assignment);
        void assignmentRemoved(db::MissionAssignmentPtr assignment);
        void assignmentChanged(db::MissionAssignmentPtr assignment);

        void vehicleAdded(db::VehiclePtr vehicle);
        void vehicleRemoved(db::VehiclePtr vehicle);
        void vehicleChanged(db::VehiclePtr vehicle);

        void linkAdded(db::LinkDescriptionPtr link);
        void linkRemoved(db::LinkDescriptionPtr link);
        void linkChanged(db::LinkDescriptionPtr link);

        void videoSourceAdded(db::VideoSourcePtr videoSource);
        void videoSourceChanged(db::VideoSourcePtr videoSource);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DB_FACADE_H
