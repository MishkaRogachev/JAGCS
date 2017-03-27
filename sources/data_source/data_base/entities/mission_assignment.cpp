#include "mission_assignment.h"

using namespace data_source;

MissionAssignment::MissionAssignment(int id):
    BaseEntity(id),
    m_missionId(0),
    m_vehicleId(0),
    m_status(NotActual)
{}

QString MissionAssignment::tableName()
{
    return "mission_assignments";
}

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
