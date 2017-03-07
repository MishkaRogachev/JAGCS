#include "mission_service.h"

// Qt
#include <QApplication>
#include <QDebug>

// Internal
#include "mission.h"
#include "mission_vehicle.h"
#include "abstract_vehicle.h"

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

    connect(mission, &Mission::assigned,
            this, &MissionService::onMissionAssigned);
    connect(mission, &Mission::unassigned,
            this, &MissionService::onMissionUnassigned);

    emit missionAdded(mission);
    if (mission->assignedVehicle()) emit missionAssigned(mission);
}

void MissionService::addNewMission()
{
    this->addMission(new Mission(this));
}

void MissionService::addVehiclesMision(AbstractVehicle* vehicle)
{
    Mission* mission = new Mission(this);
    this->addMission(mission);
    mission->assignVehicle(vehicle);
    this->downloadMission(mission);
    qApp->processEvents(); //force QtLocation to redraw
}

void MissionService::removeMission(Mission* mission)
{
    d->missions.removeOne(mission);

    disconnect(mission, 0, this, 0);

    if (mission->assignedVehicle()) emit missionUnassigned(mission);
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

void MissionService::onMissionAssigned()
{
    emit missionAssigned(qobject_cast<Mission*>(this->sender()));
}

void MissionService::onMissionUnassigned()
{
    emit missionUnassigned(qobject_cast<Mission*>(this->sender()));
}
