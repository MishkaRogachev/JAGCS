#include "mission_service.h"

// Internal
#include "db_facade.h"

#include "mission.h"
#include "mission_item.h"
#include "mission_assignment.h"
#include "vehicle_description.h"

using namespace db;
using namespace domain;

class MissionService::Impl
{
public:
    DbFacade* facade;

    MissionPtrList missions;
};

MissionService::MissionService(db::DbFacade* facade, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->facade = facade;

    d->missions = facade->loadMissions();
}

MissionService::~MissionService()
{
    for (const MissionPtr& mission: d->missions)
    {
        d->facade->save(mission);
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
            d->facade->vehicleAssignment(vehicle->id());
    if (!vehicleAssignment) return db::MissionPtr();

    return d->facade->readMission(vehicleAssignment->missionId());
}

MissionAssignmentPtr MissionService::missionAssignment(const MissionPtr& mission) const
{
    return d->facade->missionAssignment(mission->id());
}

void MissionService::assign(const MissionPtr& mission, const VehicleDescriptionPtr& vehicle)
{
    // Unassign current vehicle's assignment
    db::MissionAssignmentPtr vehicleAssignment =
            d->facade->vehicleAssignment(vehicle->id());
    if (vehicleAssignment)
    {
        if (vehicleAssignment->missionId() == mission->id()) return;

        if (!d->facade->remove(vehicleAssignment)) return;
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

    d->facade->save(assignment);
    emit (isNew ? assignmentAdded(assignment) : assignmentChanged(assignment));
}

void MissionService::unassign(const MissionPtr& mission)
{
    db::MissionAssignmentPtr assignment = this->missionAssignment(mission);
    if (!assignment.isNull()) d->facade->remove(assignment);
}

MissionItemPtrList MissionService::missionItems(const MissionPtr& mission) const
{
    return d->facade->missionItems(mission->id());
}

MissionItemPtr MissionService::missionItem(const MissionPtr& mission,
                                           int sequence) const
{
    return d->facade->missionItem(mission->id(), sequence);
}

void MissionService::saveMission(const MissionPtr& mission)
{
    if (!d->facade->save(mission)) return;

    if (!d->missions.contains(mission))
    {
        d->missions.append(mission);
        emit missionAdded(mission);
    }
}

void MissionService::removeMission(const MissionPtr& mission)
{
    if (!d->facade->remove(mission)) return;

    d->missions.removeOne(mission);
    emit missionRemoved(mission);
}

void MissionService::saveMissionItem(const MissionItemPtr& item)
{
    bool isNew = item->id() == 0;

    if (!d->facade->save(item)) return;
    if (isNew) emit missionItemAdded(item);
}

void MissionService::removeMissionItem(const MissionItemPtr& item)
{
    // FIXME: fix items sequence
    if (!d->facade->remove(item)) return;
    emit missionItemRemoved(item);
}

void MissionService::addNewMissionItem(const MissionPtr& mission)
{
    db::MissionItemPtr item = db::MissionItemPtr::create();
    db::MissionItemPtrList items = d->facade->missionItems(mission->id());

    item->setMissionId(mission->id());
    item->setCommand(items.count() ?
                         db::MissionItem::Waypoint : db::MissionItem::Takeoff);
    item->setSequence(items.count());

    if (d->facade->save(item)) emit missionItemAdded(item);
}
