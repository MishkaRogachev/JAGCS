#ifndef MISSION_ASSIGNMENT_H
#define MISSION_ASSIGNMENT_H

// Internal
#include "base_dao.h"

// Qt
#include <QVector>

namespace dao
{
    class MissionAssignment: public BaseDao
    {
        Q_GADGET

        Q_PROPERTY(int missionId READ missionId WRITE setMissionId)
        Q_PROPERTY(int vehicleId READ vehicleId WRITE setVehicleId)

    public:
        enum Status: quint8
        {
            NotActual = 0,
            Downloading,
            Uploading,
            Actual
        };

        int missionId() const;
        void setMissionId(int missionId);

        int vehicleId() const;
        void setVehicleId(int vehicleId);

        Status status() const;
        void setStatus(Status status);

    private:
        int m_missionId = 0;
        int m_vehicleId = 0;

        Status m_status = NotActual;

        Q_ENUM(Status)
    };
}

#endif // MISSION_ASSIGNMENT_H
