#ifndef MISSION_ASSIGNMENT_H
#define MISSION_ASSIGNMENT_H

// Internal
#include "base_entity.h"

namespace data_source
{
    class MissionAssignment: public BaseEntity
    {
        Q_GADGET

    public:
        MissionAssignment(int id = 0);

        int missionId() const;
        void setMissionId(int missionId);

        int vehicleId() const;
        void setVehicleId(int vehicleId);

    private:
        int m_missionId;
        int m_vehicleId;
    };
}

#endif // MISSION_ASSIGNMENT_H
