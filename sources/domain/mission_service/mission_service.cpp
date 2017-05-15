#include "mission_service.h"

// Qt
#include <QDebug>

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

MissionPtr MissionService::mission(int id) const
{
    return d->facade->readMission(id);
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

MissionAssignmentPtr MissionService::vehicleAssignment(const VehicleDescriptionPtr& vehicle) const
{
    return d->facade->vehicleAssignment(vehicle->id());
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

MissionItemPtrList MissionService::missionItems() const
{
    return d->facade->missionItems();
}

MissionItemPtrList MissionService::missionItems(int missionId) const
{
    return d->facade->missionItems(missionId);
}

MissionItemPtr MissionService::missionItem(int missionId, int sequence) const
{
    return d->facade->missionItem(missionId, sequence);
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
    for (const db::MissionItemPtr& item: this->missionItems(mission->id()))
    {
        this->removeMissionItem(item);
    }

    if (!d->facade->remove(mission)) return;

    d->missions.removeOne(mission);
    emit missionRemoved(mission);
}

void MissionService::saveMissionItem(const MissionItemPtr& item)
{
    bool isNew = item->id() == 0;

    if (!d->facade->save(item)) return;

    if (isNew)
    {
        this->fixSequenceOrder(item->missionId());
        emit missionItemAdded(item);
    }
    else
    {
        emit missionItemChanged(item);
    }
}

void MissionService::removeMissionItem(const MissionItemPtr& item)
{
    if (!d->facade->remove(item)) return;
    this->fixSequenceOrder(item->missionId());

    emit missionItemRemoved(item);
}

void MissionService::addNewMissionItem(int missionId)
{
    db::MissionPtr mission = this->mission(missionId);
    if (mission.isNull()) return;

    db::MissionItemPtr item = db::MissionItemPtr::create();
    item->setMissionId(missionId);

    if (mission->count())
    {
        item->setCommand(db::MissionItem::Waypoint);

        db::MissionItemPtr lastItem = this->missionItem(missionId, mission->count());
        if (lastItem->isAltitudeRelative())
        {
            item->setAltitude(0);
            item->setAltitudeRelative(true);
        }
        else
        {
            item->setAltitude(lastItem->altitude());
        }
    }
    else
    {
        item->setCommand(db::MissionItem::Takeoff);
        item->setAltitude(0);
        item->setAltitudeRelative(true);
    }

    item->setSequence(mission->count() + 1);
    mission->setCount(item->sequence());

    if (d->facade->save(item) &&
        d->facade->save(mission)) emit missionItemAdded(item);
}

void MissionService::saveMissionItems(const MissionPtr& mission)
{
    for (const db::MissionItemPtr& item: d->facade->missionItems(mission->id()))
    {
        this->saveMissionItem(item);
    }
}

void MissionService::fixSequenceOrder(int missionId)
{
    int counter = 0;
    for (const db::MissionItemPtr& item : d->facade->missionItems(missionId))
    {
        counter++;
        if (item->sequence() != counter)
        {
            item->setSequence(counter);
            d->facade->save(item);
            emit missionItemChanged(item);
        }
    }

    db::MissionPtr mission = this->mission(missionId);
    mission->setCount(counter);
}
