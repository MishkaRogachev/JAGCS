#include "mission_vehicle.h"

// Internal
#include "mission.h"
#include "vehicle.h"
#include "home_mission_item.h"

using namespace domain;

MissionVehicle::MissionVehicle(Mission* mission, Vehicle* vehicle):
    QObject(vehicle),
    m_mission(mission),
    m_vehicle(vehicle)
{
    Q_ASSERT(mission);
}

Mission* MissionVehicle::mission() const
{
    return m_mission;
}

Vehicle* MissionVehicle::vehicle() const
{
    return m_vehicle;
}

void MissionVehicle::setVehicle(Vehicle* vehicle)
{
    if (m_vehicle == vehicle) return;

    if (m_vehicle)
    {
        disconnect(m_vehicle, &Vehicle::homePositionChanged,
                   this, &MissionVehicle::onHomePositionChanged);
    }

    m_vehicle = vehicle;

    if (m_vehicle)
    {
        connect(m_vehicle, &Vehicle::homePositionChanged,
                this, &MissionVehicle::onHomePositionChanged);
    }

    emit vehicleChanged(m_vehicle);
}

void MissionVehicle::onHomePositionChanged(const Position& homePosition)
{
    if (!m_mission->count())
    {
        m_mission->addNewMissionItem();
    }

    HomeMissionitem* home = qobject_cast<HomeMissionitem*>(m_mission->item(0));
    if (home)
    {
        home->setLatitude(homePosition.coordinate().latitude());
        home->setLongitude(homePosition.coordinate().longitude());
    }
}
