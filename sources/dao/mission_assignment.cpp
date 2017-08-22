#include "mission_assignment.h"

using namespace dao;

int MissionAssignment::missionId() const
{
    return m_missionId;
}

void MissionAssignment::setMissionId(int missionId)
{
    m_missionId = missionId;
}

int MissionAssignment::vehicleId() const
{
    return m_vehicleId;
}

void MissionAssignment::setVehicleId(int vehicleId)
{
    m_vehicleId = vehicleId;
}

MissionAssignment::Status MissionAssignment::status() const
{
    return m_status;
}

void MissionAssignment::setStatus(Status status)
{
    m_status = status;
}
