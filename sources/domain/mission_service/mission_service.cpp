#include "mission_service.h"

// Internal
#include "mission.h"
#include "mission_vehicle.h"

using namespace domain;

class MissionService::Impl
{
public:
    QList<Mission*> missions;

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

const QList<Mission*>& MissionService::missions() const
{
    return d->missions;
}

Mission* MissionService::missionForVehicleId(uint8_t id)
{
    for (Mission* mission: d->missions)
    {
        if (mission->assignment()->vehicleId() != id) continue;

        return mission;
    }

    return nullptr;
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
    emit missionRemoved(mission);
}

void MissionService::deleteMission(Mission* mission)
{
    this->removeMission(mission);
    delete mission;
}

void MissionService::downloadMission(Mission* mission)
{
    if (!mission->assignment()->vehicle()) return;

    emit requestMission(mission->assignment()->vehicleId());
}

void MissionService::uploadMission(Mission* mission)
{
    if (!mission->assignment()->vehicle()) return;

    emit sendMission(mission->assignment()->vehicleId());
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
