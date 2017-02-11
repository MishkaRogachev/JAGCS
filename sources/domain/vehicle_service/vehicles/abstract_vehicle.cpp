#include "abstract_vehicle.h"

// Internal
#include "mission.h"

using namespace domain;

AbstractVehicle::AbstractVehicle(uint8_t vehicleId, int type, QObject* parent):
    QObject(parent),
    m_vehicleId(vehicleId),
    m_type(type),
    m_assignedMission(nullptr)
{}

AbstractVehicle::~AbstractVehicle()
{
    if (m_assignedMission) this->unassignMission();
}

uint8_t AbstractVehicle::vehicleId() const
{
    return m_vehicleId;
}

int AbstractVehicle::type() const
{
    return m_type;
}

Mission* AbstractVehicle::assignedMission() const
{
    return m_assignedMission;
}

void AbstractVehicle::assignMission(Mission* mission)
{
    if (m_assignedMission == mission) return;

    if (m_assignedMission)
    {
        m_assignedMission->unassignVehicle();
    }

    m_assignedMission = mission;

    if (m_assignedMission)
    {
        m_assignedMission->assignVehicle(this);
    }

    emit assignedMissionChanged(mission);
}

void AbstractVehicle::unassignMission()
{
    this->assignMission(nullptr);
}

