#include "mission_service.h"

// Internal
#include "mission.h"
#include "mission_item.h"
#include "mission_assignment.h"

#include "generic_repository.h"
#include "generic_repository_impl.h"

using namespace dao;
using namespace domain;

class MissionService::Impl
{
public:
    GenericRepository<Mission> missionRepository;
    GenericRepository<MissionItem> itemRepository;
    GenericRepository<MissionAssignment> assignmentRepository;

    Impl():
        missionRepository("missions"),
        itemRepository("mission_items"),
        assignmentRepository("mission_assignments")
    {}
};

MissionService::MissionService(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

MissionService::~MissionService()
{}

MissionPtr MissionService::mission(int id, bool reload)
{
    return d->missionRepository.read(id, reload);
}

MissionItemPtr MissionService::missionItem(int id, bool reload)
{
    return d->itemRepository.read(id, reload);
}

MissionAssignmentPtr MissionService::assignment(int id, bool reload)
{
    return d->assignmentRepository.read(id, reload);
}

MissionPtrList MissionService::missions(const QString& condition, bool reload)
{
    MissionPtrList list;

    for (int id: d->missionRepository.selectId(condition))
    {
        list.append(this->mission(id, reload));
    }

    return list;
}

MissionItemPtrList MissionService::missionItems(const QString& condition, bool reload)
{
    MissionItemPtrList list;

    for (int id: d->itemRepository.selectId(condition))
    {
        list.append(this->missionItem(id, reload));
    }
    return list;
}

MissionAssignmentPtr MissionService::missionAssignment(int missionId)
{
    for (int id: d->assignmentRepository.selectId(
             QString("missionId = %1").arg(missionId)))
    {
        return this->assignment(id);
    }
    return MissionAssignmentPtr();
}

MissionAssignmentPtr MissionService::vehicleAssignment(int vehicleId)
{
    for (int id: d->assignmentRepository.selectId(
             QString("vehicleId = %1").arg(vehicleId)))
    {
        return this->assignment(id);
    }
    return MissionAssignmentPtr();
}

MissionItemPtrList MissionService::missionItems(int missionId)
{
    return this->missionItems(QString("missionId = %1 ORDER BY sequence").arg(
                               missionId));
}

MissionItemPtr MissionService::missionItem(int missionId, int sequence)
{
    for (int id: d->itemRepository.selectId(
             QString("missionId = %1 AND sequence = %2").arg(missionId).arg(sequence)))
    {
        return this->missionItem(id);
    }
    return MissionItemPtr();
}

bool MissionService::save(const MissionPtr& mission)
{
    bool isNew = mission->id() == 0;
    if (!d->missionRepository.save(mission)) return false;

    emit (isNew ? missionAdded(mission) : missionChanged(mission));
    return true;
}

bool MissionService::save(const MissionItemPtr& item)
{
    bool isNew = item->id() == 0;
    if (!d->itemRepository.save(item)) return false;

    if (isNew)
    {
        this->fixMissionItemOrder(item->missionId());
        emit missionItemAdded(item);
    }
    else
    {
        emit missionItemChanged(item);  // TODO: check changed flag
    }

    return true;
}

bool MissionService::save(const MissionAssignmentPtr& assignment)
{
    bool isNew = assignment->id() == 0;
    if (!d->assignmentRepository.save(assignment)) return false;

    emit (isNew ? assignmentAdded(assignment) : assignmentChanged(assignment));
    return true;
}

bool MissionService::remove(const MissionPtr& mission)
{
    MissionAssignmentPtr assignment = this->missionAssignment(mission->id());
    if (assignment && !this->remove(assignment)) return false;

    for (const MissionItemPtr& item: this->missionItems(mission->id()))
    {
        if (!this->remove(item)) return false;
    }

    if (!d->missionRepository.remove(mission)) return false;

    emit missionRemoved(mission);
    return true;
}

bool MissionService::remove(const MissionItemPtr& item)
{
    if (!d->itemRepository.remove(item)) return false;

    this->fixMissionItemOrder(item->missionId());
    emit missionItemRemoved(item);
    return true;
}

bool MissionService::remove(const MissionAssignmentPtr& assignment)
{
    if (!d->assignmentRepository.remove(assignment)) return false;

    emit assignmentRemoved(assignment);
    return true;
}

void MissionService::addNewMissionItem(int missionId)
{
    MissionPtr mission = this->mission(missionId);
    if (mission.isNull()) return;

    MissionItemPtr item = MissionItemPtr::create();
    item->setMissionId(missionId);

    if (mission->count() > 1) // TODO: default parms to settings
    {
        item->setCommand(MissionItem::Waypoint);

        MissionItemPtr lastItem = this->missionItem(missionId, mission->count() - 1);

        item->setAltitudeRelative(lastItem->isAltitudeRelative());
        item->setAltitude(lastItem->altitude());
        item->setRadius(0);
    }
    else if (mission->count() == 1)
    {
        item->setCommand(MissionItem::Takeoff);
        item->setAltitude(30);
        item->setAltitudeRelative(true);
        item->setPitch(15);
    }
    else
    {
        item->setCommand(MissionItem::Home);
        item->setAltitude(0);
        item->setAltitudeRelative(false);
    }

    item->setSequence(mission->count());

    this->save(item);
}

void MissionService::saveMissionItems(int missionId)
{
    for (const MissionItemPtr& item: this->missionItems(missionId))
    {
        this->save(item);
    }
}

void MissionService::fixMissionItemOrder(int missionId)
{
    int counter = 0;
    for (const MissionItemPtr& item : this->missionItems(missionId))
    {
        if (item->sequence() != counter)
        {
            item->setSequence(counter);
            this->save(item);
        }
        counter++;
    }

    MissionPtr mission = this->mission(missionId);
    if (mission->count() != counter)
    {
        mission->setCount(counter);
        this->save(mission);
    }
}

void MissionService::assign(int missionId, int vehicleId)
{
    // Unassign current vehicle's assignment
    MissionAssignmentPtr vehicleAssignment = this->vehicleAssignment(vehicleId);
    if (vehicleAssignment)
    {
        if (vehicleAssignment->missionId() == missionId) return;

        if (!this->remove(vehicleAssignment)) return;
    }

    // Read current mission assignment, if exist
    MissionAssignmentPtr missionAssignment = this->missionAssignment(missionId);
    if (missionAssignment.isNull())
    {
        missionAssignment = MissionAssignmentPtr::create();
        missionAssignment->setMissionId(missionId);
    }
    else if (missionAssignment->vehicleId() == vehicleId) return;

    missionAssignment->setVehicleId(vehicleId);

    this->save(missionAssignment);

    for (const dao::MissionItemPtr& item: this->missionItems(missionId))
    {
        item->setStatus(MissionItem::NotActual);
        emit missionItemChanged(item);
    }
}

void MissionService::unassign(int missionId)
{
    MissionAssignmentPtr assignment = this->missionAssignment(missionId);
    if (!assignment.isNull()) this->remove(assignment);

    for (const dao::MissionItemPtr& item: this->missionItems(missionId))
    {
        item->setStatus(MissionItem::NotActual);
        emit missionItemChanged(item);
    }

    //  TODO: clear currend and passed statuses
}



