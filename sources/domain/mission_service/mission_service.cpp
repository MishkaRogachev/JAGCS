#include "mission_service.h"

// Qt
#include <QMap>

// Internal
#include "mission.h"

using namespace domain;

class MissionService::Impl
{
public:
    QList<Mission*> missions;
    QMap<uint8_t, Mission*> vehicleMissions;
};

MissionService::MissionService(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

MissionService::~MissionService()
{
    delete d;
}

Mission* MissionService::missionForVehicle(uint8_t id) const
{
    return d->vehicleMissions.value(id, nullptr);
}

uint8_t MissionService::vehicleForMission(Mission* mission) const
{
    return d->vehicleMissions.key(mission);
}

const QList<Mission*>& MissionService::missions() const
{
    return d->missions;
}

Mission* MissionService::requestMissionForVehicle(uint8_t id)
{
    if (!d->vehicleMissions.contains(id))
    {
        Mission* mission = new Mission(this);
        d->vehicleMissions[id] = mission;
        d->missions.append(mission);

        emit missionAdded(mission);
    }

    return d->vehicleMissions[id];
}

void MissionService::addNewMission()
{
    d->missions.append(new Mission(this));
    emit missionAdded(d->missions.last());
}

void MissionService::removeMission(Mission* mission)
{
    d->missions.removeOne(mission);

    if (d->vehicleMissions.values().contains(mission))
    {
        d->vehicleMissions.remove(d->vehicleMissions.key(mission));
    }

    emit missionRemoved(mission);
}

void MissionService::deleteMission(Mission* mission)
{
    this->removeMission(mission);
    delete mission;
}
