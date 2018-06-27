#include "mission_service.h"

// Qt
#include <QMap>
#include <QMutexLocker>
#include <QGeoCoordinate>

// Internal
#include "settings_provider.h"
#include "mission.h"
#include "mission_item.h"
#include "mission_assignment.h"
#include "vehicle.h"

#include "generic_repository.h"

using namespace dto;
using namespace domain;

class MissionService::Impl
{
public:
    QMutex mutex;

    GenericRepository<Mission> missionRepository;
    GenericRepository<MissionItem> itemRepository;
    GenericRepository<MissionAssignment> assignmentRepository;

    QMap <int, MissionItemPtr> currentItems;

    Impl():
        mutex(QMutex::Recursive),
        missionRepository("missions"),
        itemRepository("mission_items"),
        assignmentRepository("mission_assignments")
    {}

    void loadMissions(const QString& condition = QString())
    {
        for (int id: missionRepository.selectId(condition)) missionRepository.read(id);
    }

    void loadMissionItems(const QString& condition = QString())
    {
        for (int id: itemRepository.selectId(condition)) itemRepository.read(id);
    }

    void loadMissionAssignments(const QString& condition = QString())
    {
        for (int id: assignmentRepository.selectId(condition)) assignmentRepository.read(id);
    }
};

MissionService::MissionService(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    qRegisterMetaType<dto::MissionPtr>("dto::MissionPtr");
    qRegisterMetaType<dto::MissionItemPtr>("dto::MissionItemPtr");
    qRegisterMetaType<dto::MissionAssignmentPtr>("dto::MissionAssignmentPtr");

    d->loadMissions();
    d->loadMissionItems();
    d->loadMissionAssignments();
}

MissionService::~MissionService()
{}

MissionPtr MissionService::mission(int id) const
{
    QMutexLocker locker(&d->mutex);

    if (id) return d->missionRepository.read(id);
    return MissionPtr();
}

MissionItemPtr MissionService::missionItem(int id) const
{
    QMutexLocker locker(&d->mutex);

    if (id) return d->itemRepository.read(id);
    return MissionItemPtr();
}

MissionAssignmentPtr MissionService::assignment(int id) const
{
    QMutexLocker locker(&d->mutex);

    if (id) return d->assignmentRepository.read(id);
    return MissionAssignmentPtr();
}

MissionPtrList MissionService::missions() const
{
    QMutexLocker locker(&d->mutex);

    return d->missionRepository.loadedEntities();
}

MissionItemPtrList MissionService::missionItems() const
{
    QMutexLocker locker(&d->mutex);

    return d->itemRepository.loadedEntities();
}

MissionAssignmentPtrList MissionService::missionAssignments() const
{
    QMutexLocker locker(&d->mutex);

    return d->assignmentRepository.loadedEntities();
}

MissionItemPtr MissionService::currentWaypoint(int vehicleId) const
{
    QMutexLocker locker(&d->mutex);

    return d->currentItems.value(vehicleId);
}

int MissionService::isCurrentForVehicle(const MissionItemPtr& item) const
{
    return d->currentItems.key(item, 0);
}

dto::MissionItemPtr MissionService::addNewMissionItem(int missionId,
                                                      dto::MissionItem::Command command,
                                                      int sequence,
                                                      const QGeoCoordinate& coordinate)
{
    QMutexLocker locker(&d->mutex);

    dto::MissionPtr mission = this->mission(missionId);
    if (mission.isNull() || mission->count() < sequence) return dto::MissionItemPtr();

    dto::MissionItemPtr item = dto::MissionItemPtr::create();
    dto::MissionItemPtr lastItem = this->missionItem(missionId, sequence - 1);

    item->setMissionId(missionId);
    item->setCommand(command);
    item->setSequence(sequence);

    switch (command) { // TODO: to MissionItemFactory
    case dto::MissionItem::Home:
        item->setAltitude(0);
        item->setAltitudeRelative(false);
        break;
    case dto::MissionItem::Waypoint:
        if (lastItem)
        {
            item->setAltitudeRelative(lastItem->isAltitudeRelative());
            item->setAltitude(lastItem->altitude());
        }
        break;
    case dto::MissionItem::Takeoff:
        if (lastItem) item->setAltitudeRelative(true);
            item->setAltitude(settings::Provider::value(
                                  settings::parameters::defaultTakeoffAltitude).toReal());
        item->setParameter(dto::MissionItem::Pitch, settings::Provider::value(
                               settings::parameters::defaultTakeoffPitch).toReal());
        break;
    case dto::MissionItem::Landing:
        if (lastItem)
        {
            item->setAltitude(0);
            item->setAltitudeRelative(true);
        }
        break;
    default:
        break;
    }

    if (item->isPositionatedItem())
    {
        item->setLatitude(coordinate.latitude());
        item->setLongitude(coordinate.longitude());
    }

    // TODO: querry by sequence
    for (const dto::MissionItemPtr& other: this->missionItems(missionId))
    {
        if (other->sequence() < sequence) continue;

        other->setSequence(other->sequence() + 1);
        other->setStatus(dto::MissionItem::NotActual);
        this->save(other);
    }

    if (!this->save(item)) return dto::MissionItemPtr();

    dto::MissionAssignmentPtr assignment = this->missionAssignment(missionId);
    if (assignment)
    {
        assignment->setStatus(MissionAssignment::NotActual);
        emit assignmentChanged(assignment);
    }

    return item;
}

void MissionService::addNewMission(const QString& name, const QGeoCoordinate& coordinate)
{
    QMutexLocker locker(&d->mutex);

    MissionPtr mission = MissionPtr::create();
    mission->setName(name);
    this->save(mission);

    this->addNewMissionItem(mission->id(), MissionItem::Home, 0, coordinate);
}

MissionAssignmentPtr MissionService::missionAssignment(int missionId) const
{
    QMutexLocker locker(&d->mutex);

    for (const MissionAssignmentPtr& assignment: d->assignmentRepository.loadedEntities())
    {
        if (assignment->missionId() == missionId) return assignment;
    }

    return MissionAssignmentPtr();
}

MissionAssignmentPtr MissionService::vehicleAssignment(int vehicleId) const
{
    QMutexLocker locker(&d->mutex);

    for (const MissionAssignmentPtr& assignment: d->assignmentRepository.loadedEntities())
    {
        if (assignment->vehicleId() == vehicleId) return assignment;
    }

    return MissionAssignmentPtr();
}

MissionItemPtrList MissionService::missionItems(int missionId) const
{
    QMutexLocker locker(&d->mutex);

    QMap<int, MissionItemPtr> items;
    for (const MissionItemPtr& item: d->itemRepository.loadedEntities())
    {
        if (item->missionId() == missionId) items[item->sequence()] = item;
    }
    return items.values();
}

MissionItemPtr MissionService::missionItem(int missionId, int sequence) const
{
    QMutexLocker locker(&d->mutex);

    for (const MissionItemPtr& item: d->itemRepository.loadedEntities())
    {
        if (item->missionId() == missionId && item->sequence() == sequence) return item;
    }
    return MissionItemPtr();
}

bool MissionService::save(const MissionPtr& mission)
{
    QMutexLocker locker(&d->mutex);

    bool isNew = mission->id() == 0;
    if (!d->missionRepository.save(mission)) return false;

    if (isNew)
    {
        settings::Provider::setValue(settings::mission::mission + QString::number(mission->id()) +
                                     "/" + settings::visibility, true);
        emit missionAdded(mission);
    }
    else
    {
        emit missionChanged(mission);
    }

    return true;
}

bool MissionService::save(const MissionItemPtr& item)
{
    QMutexLocker locker(&d->mutex);

    bool isNew = item->id() == 0;
    item->clearSuperfluousParameters();
    if (!d->itemRepository.save(item)) return false;

    emit (isNew ? missionItemAdded(item) : missionItemChanged(item));
    if (isNew) this->fixMissionItemCount(item->missionId());

    return true;
}

bool MissionService::save(const MissionAssignmentPtr& assignment)
{
    QMutexLocker locker(&d->mutex);

    bool isNew = assignment->id() == 0;
    if (!d->assignmentRepository.save(assignment)) return false;

    emit (isNew ? assignmentAdded(assignment) : assignmentChanged(assignment));
    return true;
}

bool MissionService::remove(const MissionPtr& mission)
{
    QMutexLocker locker(&d->mutex);

    MissionAssignmentPtr assignment = this->missionAssignment(mission->id());
    if (assignment && !this->remove(assignment)) return false;

    for (const MissionItemPtr& item: this->missionItems(mission->id()))
    {
        if (!this->remove(item)) return false;
    }

    if (!d->missionRepository.remove(mission)) return false;

    settings::Provider::remove(settings::mission::mission + QString::number(mission->id()));

    emit missionRemoved(mission);
    return true;
}

bool MissionService::remove(const MissionItemPtr& item)
{
    QMutexLocker locker(&d->mutex);

    // TODO: remove from current
    if (!d->itemRepository.remove(item)) return false;

    this->fixMissionItemOrder(item->missionId());
    emit missionItemRemoved(item);
    return true;
}

bool MissionService::remove(const MissionAssignmentPtr& assignment)
{
    QMutexLocker locker(&d->mutex);

    for (const dto::MissionItemPtr& item: this->missionItems(assignment->missionId()))
    {
        item->setStatus(MissionItem::NotActual);
        emit missionItemChanged(item);
    }

    for (const dto::MissionItemPtr& item: d->currentItems.values())
    {
        if (item->missionId() != assignment->missionId()) continue;

        d->currentItems.remove(d->currentItems.key(item));
        emit missionItemChanged(item);
    }

    if (!d->assignmentRepository.remove(assignment)) return false;

    emit assignmentRemoved(assignment);
    return true;
}

void MissionService::unload(const MissionPtr& mission)
{
    QMutexLocker locker(&d->mutex);

    d->missionRepository.unload(mission->id());
}

void MissionService::unload(const MissionItemPtr& item)
{
    QMutexLocker locker(&d->mutex);

    d->itemRepository.unload(item->id());
}

void MissionService::unload(const MissionAssignmentPtr& assignment)
{
    QMutexLocker locker(&d->mutex);

    d->assignmentRepository.unload(assignment->id());
}

void MissionService::fixMissionItemOrder(int missionId)
{
    QMutexLocker locker(&d->mutex);

    int counter = 0;
    for (const MissionItemPtr& item : this->missionItems(missionId))
    {
        if (item->sequence() != counter)
        {
            item->setSequence(counter);
            item->setStatus(MissionItem::NotActual);
            this->save(item);
        }
        counter++;
    }

    this->fixMissionItemCount(missionId);
}

void MissionService::fixMissionItemCount(int missionId)
{
    int count = this->missionItems(missionId).count();
    MissionPtr mission = this->mission(missionId);

    if (mission->count() != count)
    {
        mission->setCount(count);
        this->save(mission);
    }
}

void MissionService::assign(int missionId, int vehicleId)
{
    QMutexLocker locker(&d->mutex);

    // Unassign current vehicle's assignment
    MissionAssignmentPtr vehicleAssignment = this->vehicleAssignment(vehicleId);
    if (vehicleAssignment)
    {
        if (vehicleAssignment->missionId() == missionId) return;

        this->unassign(vehicleAssignment->missionId());
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

    for (const dto::MissionItemPtr& item: this->missionItems(missionId))
    {
        item->setStatus(MissionItem::NotActual);
        emit missionItemChanged(item);
    }
}

void MissionService::unassign(int missionId)
{
    QMutexLocker locker(&d->mutex);

    MissionAssignmentPtr assignment = this->missionAssignment(missionId);
    if (assignment.isNull()) return;

    MissionItemPtr oldOne =d->currentItems.take(assignment->vehicleId());
    emit currentItemChanged(assignment->vehicleId(), oldOne, MissionItemPtr());
    this->remove(assignment);
}

void MissionService::setCurrentItem(int vehicleId, const MissionItemPtr& current)
{
    QMutexLocker locker(&d->mutex);

    MissionItemPtr oldCurrent = d->currentItems.value(vehicleId);
    if (oldCurrent == current) return;

    if (current)
    {
        d->currentItems[vehicleId] = current;
        emit missionItemChanged(current);
    }
    else if (oldCurrent) d->currentItems.remove(vehicleId);

    emit currentItemChanged(vehicleId, oldCurrent, current);
}

void MissionService::swapItems(const MissionItemPtr& first, const MissionItemPtr& second)
{
    QMutexLocker locker(&d->mutex);

    int seq = first->sequence();
    first->setSequence(second->sequence());
    second->setSequence(seq);

    if (!d->itemRepository.save(first)) return;
    if (!d->itemRepository.save(second)) return;

    emit missionItemChanged(first);
    emit missionItemChanged(second);
}

void MissionService::onVehicleChanged(const VehiclePtr& vehicle)
{
    if (vehicle->isOnline()) return;

    dto::MissionAssignmentPtr assignment = this->vehicleAssignment(vehicle->id());
    if (assignment &&
        (assignment->status() == dto::MissionAssignment::Downloading ||
         assignment->status() == dto::MissionAssignment::Uploading))
    {
        this->cancelSync(assignment);
    }
}

