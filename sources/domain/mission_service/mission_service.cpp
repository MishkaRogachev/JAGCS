#include "mission_service.h"

// Internal
#include "db_entry.h"

#include "mission.h"
#include "mission_item.h"
#include "mission_assignment.h"
#include "vehicle_description.h"

using namespace db;
using namespace domain;

class MissionService::Impl
{
public:
    DbEntry* entry;

    MissionPtrList missions;
};

MissionService::MissionService(db::DbEntry* entry, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->entry = entry;

    d->missions = entry->loadMissions();
}

MissionService::~MissionService()
{
    for (const MissionPtr& mission: d->missions)
    {
        d->entry->save(mission);
    }
}

MissionPtrList MissionService::missions() const
{
    return d->missions;
}

MissionPtr MissionService::missionByName(const QString& name) const
{
    for (const MissionPtr& mission: d->missions)
    {
        if (mission->name() == name) return mission;
    }
    return MissionPtr();
}

MissionPtr MissionService::missionByVehicle(const VehicleDescriptionPtr& vehicle) const
{
    db::MissionAssignmentPtr vehicleAssignment =
            d->entry->vehicleAssignment(vehicle->id());
    if (!vehicleAssignment) return db::MissionPtr();

    return d->entry->readMission(vehicleAssignment->missionId());
}

MissionAssignmentPtr MissionService::missionAssignment(const MissionPtr& mission) const
{
    return d->entry->missionAssignment(mission->id());
}

void MissionService::assign(const MissionPtr& mission, const VehicleDescriptionPtr& vehicle)
{
    // Unassign current vehicle's assignment
    db::MissionAssignmentPtr vehicleAssignment =
            d->entry->vehicleAssignment(vehicle->id());
    if (vehicleAssignment)
    {
        if (vehicleAssignment->missionId() == mission->id()) return;

        if (!d->entry->remove(vehicleAssignment)) return;
        emit assignmentRemoved(vehicleAssignment);
    }

    // Read current mission assignment, if exist
    MissionAssignmentPtr assignment = this->missionAssignment(mission);
    if (assignment.isNull())
    {
        assignment = MissionAssignmentPtr::create();
        assignment->setMissionId(mission->id());
    }
    else if (assignment->vehicleId() == vehicle->id()) return;

    bool isNew = assignment->id() == 0;
    assignment->setVehicleId(vehicle->id());
    assignment->setStatus(MissionAssignment::NotActual);

    d->entry->save(assignment);
    emit (isNew ? assignmentAdded(assignment) : assignmentChanged(assignment));
}

void MissionService::unassign(const MissionPtr& mission)
{
    db::MissionAssignmentPtr assignment = this->missionAssignment(mission);
    if (!assignment.isNull()) d->entry->remove(assignment);
}

void MissionService::saveMission(const MissionPtr& mission)
{
    if (!d->entry->save(mission)) return;

    if (!d->missions.contains(mission))
    {
        d->missions.append(mission);
        emit missionAdded(mission);
    }
}

void MissionService::removeMission(const MissionPtr& mission)
{
    db::MissionAssignmentPtr assignment = this->missionAssignment(mission);

    if (!assignment.isNull()) d->entry->remove(assignment);
    if (!d->entry->remove(mission)) return;

    d->missions.removeOne(mission);
    emit missionRemoved(mission);
}

void MissionService::saveMissionItem(const MissionItemPtr& item)
{
    bool isNew = item->id() == 0;

    if (!d->entry->save(item)) return;
    if (isNew) emit missionItemAdded(item);
}

void MissionService::removeMissionItem(const MissionItemPtr& item)
{
    if (!d->entry->remove(item)) return;
    emit missionItemRemoved(item);
}
