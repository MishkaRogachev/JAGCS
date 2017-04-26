#ifndef MISSION_SERVICE_H
#define MISSION_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

namespace db
{
    class DbEntry;
}

namespace domain
{
    class MissionService: public QObject
    {
        Q_OBJECT

    public:
        explicit MissionService(db::DbEntry* entry, QObject* parent = nullptr);
        ~MissionService() override;

        db::MissionPtrList missions() const;
        db::MissionPtr findMissionByName(const QString& name) const;

        db::MissionAssignmentPtr assignment(const db::MissionPtr& mission);
        void assign(const db::MissionPtr& mission,
                    const db::VehicleDescriptionPtr& vehicle);
        void unassign(const db::MissionPtr& mission);

    public slots:
        void saveMission(const db::MissionPtr& mission);
        void removeMission(const db::MissionPtr& mission);
        void saveMissionItem(const db::MissionItemPtr& item);
        void removeMissionItem(const db::MissionItemPtr& item);

    signals:
        void missionAdded(const db::MissionPtr& mission);
        void missionRemoved(const db::MissionPtr& mission);
        void missionItemAdded(const db::MissionItemPtr& mission);
        void missionItemRemoved(const db::MissionItemPtr& mission);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_SERVICE_H
