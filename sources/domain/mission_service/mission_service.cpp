#include "mission_service.h"

// Internal
#include "mission.h"
#include "mission_vehicle.h"

using namespace domain;

class MissionService::Impl
{
public:
    QList<Mission*> missions;
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

QList<Mission*> MissionService::assignedMissions() const
{
    QList<Mission*> assigned;

    for (Mission* mission: d->missions)
    {
        if (mission->assignment()->vehicle())
            assigned.append(mission);
    }

    return assigned;
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

void MissionService::addMission(Mission* mission)
{
    d->missions.append(mission);
    emit missionAdded(mission);
}

void MissionService::addNewMission()
{
    this->addMission(new Mission(this));
}

void MissionService::addVehiclesMision(Vehicle* vehicle)
{
    Mission* mission = new Mission(this);
    mission->assignVehicle(vehicle);
    this->addMission(mission);
    this->downloadMission(mission);
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

    mission->assignment()->setStatus(MissionVehicle::Downloading);
    emit requestMission(mission->assignment()->vehicleId());
}

void MissionService::uploadMission(Mission* mission)
{
    if (!mission->assignment()->vehicle()) return;

    mission->assignment()->setStatus(MissionVehicle::Uploading);
    emit sendMission(mission->assignment()->vehicleId());
}
