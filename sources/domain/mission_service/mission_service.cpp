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

    int currentCount = 0;
    int totalCount = 0;
};

MissionService::MissionService(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

MissionService::~MissionService()
{
    while (!d->missions.isEmpty())
        this->removeMission(d->missions.first());

    delete d;
}

Mission* MissionService::missionForVehicle(uint8_t vehicleId) const
{
    return d->vehicleMissions.value(vehicleId, nullptr);
}

uint8_t MissionService::vehicleForMission(Mission* mission) const
{
    return d->vehicleMissions.key(mission);
}

const QList<Mission*>& MissionService::missions() const
{
    return d->missions;
}

Mission* MissionService::requestMissionForVehicle(uint8_t vehicleId)
{
    if (!d->vehicleMissions.contains(vehicleId))
    {
        Mission* mission = new Mission(this);
        d->vehicleMissions[vehicleId] = mission;
        d->missions.append(mission);

        emit missionAdded(mission);
    }

    return d->vehicleMissions[vehicleId];
}

int MissionService::currentCount() const
{
    return d->currentCount;
}

int MissionService::totalCount() const
{
    return d->totalCount;
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

void MissionService::setVehicleForMission(uint8_t vehicleId,
                                          Mission* mission) const
{
    if (mission)
    {
        d->vehicleMissions[vehicleId] = mission;
    }
    else
    {
        d->vehicleMissions.remove(vehicleId);
    }
}

void MissionService::setCurrentCount(int currentCount)
{
    if (d->currentCount == currentCount) return;

    d->currentCount = currentCount;
    emit currentCountChanged(currentCount);
}

void MissionService::setTotalCount(int totalCount)
{
    if (d->totalCount == totalCount) return;

    d->totalCount = totalCount;
    emit totalCountChanged(totalCount);
}
