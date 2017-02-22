#include "abstract_vehicle.h"

// Qt
#include <QDebug>

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

int AbstractVehicle::missionItems() const
{
    return m_assignedMission ? m_assignedMission->count() : 0;
}

void AbstractVehicle::assignMission(Mission* mission)
{
    if (m_assignedMission == mission) return;

    if (m_assignedMission)
    {
        m_assignedMission->unassignVehicle();
        disconnect(m_assignedMission, 0, this, 0);
    }

    m_assignedMission = mission;

    if (m_assignedMission)
    {
        m_assignedMission->assignVehicle(this);
        connect(m_assignedMission, &Mission::missionItemsChanged, this,
                [this]() { emit missionItemsChanged(this->missionItems()); });
    }

    emit missionItemsChanged(this->missionItems());
    emit assignedMissionChanged(mission);
}

void AbstractVehicle::unassignMission()
{
    this->assignMission(nullptr);
}
