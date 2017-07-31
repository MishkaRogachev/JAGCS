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
        int missionId() const;
        void setMissionId(int missionId);

        int vehicleId() const;
        void setVehicleId(int vehicleId);

    private:
        int m_missionId = 0;
        int m_vehicleId = 0;
    };
}

#endif // MISSION_ASSIGNMENT_H
