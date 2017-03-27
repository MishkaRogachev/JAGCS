#ifndef MISSION_ASSIGNMENT_H
#define MISSION_ASSIGNMENT_H

// Internal
#include "base_entity.h"

namespace data_source
{
    class MissionAssignment: public BaseEntity
    {
        Q_GADGET

        Q_PROPERTY(int missionId READ missionId WRITE setMissionId)
        Q_PROPERTY(int vehicleId READ vehicleId WRITE setVehicleId)
        Q_PROPERTY(Status status READ status WRITE setStatus)

    public:
        enum Status
        {
            Idle,
            Downloading,
            Uploading,
            Actual,
            NotActual
        };

        MissionAssignment(int id = 0);

        static QString tableName();

        int missionId() const;
        void setMissionId(int missionId);

        int vehicleId() const;
        void setVehicleId(int vehicleId);

        Status status() const;
        void setStatus(Status status);

    private:
        int m_missionId;
        int m_vehicleId;
        Status m_status;
    };
}

#endif // MISSION_ASSIGNMENT_H
