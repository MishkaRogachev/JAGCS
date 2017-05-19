#include "mission_assignment.h"

using namespace db;

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

const QVector<MissionAssignment::Status>& MissionAssignment::statuses() const
{
    return m_statuses;
}

QVector<MissionAssignment::Status>& MissionAssignment::statuses()
{
    return m_statuses;
}

