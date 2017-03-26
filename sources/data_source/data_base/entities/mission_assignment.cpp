#include "mission_assignment.h"

using namespace data_source;

MissionAssignment::MissionAssignment(int id):
    BaseEntity(id),
    m_missionId(0),
    m_vehicleId(0)
{}

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
