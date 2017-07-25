#ifndef DB_FACADE_H
#define DB_FACADE_H

// Qt
#include <QObject>

// Internal
#include "dao_traits.h"

namespace db
{
    // TODO: work with db in separated thread
    class DbFacade: public QObject
    {
        Q_OBJECT

    public:
        explicit DbFacade(QObject* parent = nullptr);
        ~DbFacade() override;

        dao::MissionPtr mission(int id, bool reload = false);
        dao::MissionItemPtr missionItem(int id, bool reload = false);
        dao::MissionAssignmentPtr assignment(int id, bool reload = false);
        dao::VehiclePtr vehicle(int id, bool reload = false);
        dao::LinkDescriptionPtr link(int id, bool reload = false);
        dao::VideoSourcePtr videoSource(int id, bool reload = false);

        bool save(const dao::MissionPtr& mission);
        bool save(const dao::MissionItemPtr& item);
        bool save(const dao::MissionAssignmentPtr& assignment);
        bool save(const dao::VehiclePtr& vehicle);
        bool save(const dao::LinkDescriptionPtr& link);
        bool save(const dao::VideoSourcePtr& videoSource);

        bool remove(const dao::MissionPtr& mission);
        bool remove(const dao::MissionItemPtr& item);
        bool remove(const dao::MissionAssignmentPtr& assignment);
        bool remove(const dao::VehiclePtr& vehicle);
        bool remove(const dao::LinkDescriptionPtr& link);
        bool remove(const dao::VideoSourcePtr& videoSource);

        dao::LinkDescriptionPtrList links(const QString& condition = QString(), bool reload  = false);
        dao::VehiclePtrList vehicles(const QString& condition = QString(), bool reload  = false);
        dao::MissionPtrList missions(const QString& condition = QString(), bool reload  = false);
        dao::MissionItemPtrList missionItems(const QString& condition = QString(), bool reload  = false);
        dao::VideoSourcePtrList videoSources(const QString& condition = QString(), bool reload  = false);

        dao::MissionAssignmentPtr missionAssignment(int missionId);
        dao::MissionAssignmentPtr vehicleAssignment(int vehicleId);

        dao::MissionItemPtrList missionItems(int missionId);
        dao::MissionItemPtr missionItem(int missionId, int sequence);

        int vehicleIdByMavId(int mavId) const;

    public slots:
        void addNewMissionItem(int missionId);
        void saveMissionItems(int missionId);
        void fixMissionItemOrder(int missionId);

        void assign(int missionId, int vehicleId);
        void unassign(int missionId);

        void clearAll();

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

        void vehicleAdded(dao::VehiclePtr vehicle);
        void vehicleRemoved(dao::VehiclePtr vehicle);
        void vehicleChanged(dao::VehiclePtr vehicle);

        void linkAdded(dao::LinkDescriptionPtr link);
        void linkRemoved(dao::LinkDescriptionPtr link);
        void linkChanged(dao::LinkDescriptionPtr link);

        void videoSourceAdded(dao::VideoSourcePtr videoSource);
        void videoSourceRemoved(dao::VideoSourcePtr videoSource);
        void videoSourceChanged(dao::VideoSourcePtr videoSource);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DB_FACADE_H
