#ifndef MISSION_ASSIGNMENT_H
#define MISSION_ASSIGNMENT_H

// Internal
#include "base_entity.h"

// Qt
#include <QVector>

namespace db
{
    class MissionAssignment: public BaseEntity
    {
        Q_GADGET

        Q_PROPERTY(int missionId READ missionId WRITE setMissionId)
        Q_PROPERTY(int vehicleId READ vehicleId WRITE setVehicleId)

    public:
        enum Status: quint8
        {
            Unknown = 0,
            NotActual,
            Downloading,
            Uploading,
            Actual
        };

        int missionId() const;
        void setMissionId(int missionId);

        int vehicleId() const;
        void setVehicleId(int vehicleId);

        const QVector<Status>& statuses() const;
        QVector<Status>& statuses();

    private:
        int m_missionId = 0;
        int m_vehicleId = 0;

        QVector<Status> m_statuses;

        Q_ENUM(Status)
    };
}

#endif // MISSION_ASSIGNMENT_H
