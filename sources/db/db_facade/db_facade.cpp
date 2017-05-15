#include "db_facade.h"

// Qt
#include <QDebug>

// Internal
#include "generic_repository.h"
#include "generic_repository_impl.h"

#include "mission.h"
#include "mission_item.h"
#include "mission_assignment.h"
#include "vehicle_description.h"
#include "link_description.h"

using namespace db;

class DbFacade::Impl
{
public:
    GenericRepository<Mission> missionRepository;
    GenericRepository<MissionItem> itemRepository;
    GenericRepository<VehicleDescription> vehicleRepository;
    GenericRepository<MissionAssignment> assignmentRepository;
    GenericRepository<LinkDescription> linkRepository;

    Impl():
        missionRepository("missions"),
        itemRepository("mission_items"),
        vehicleRepository("vehicles"),
        assignmentRepository("mission_assignments"),
        linkRepository("links")
    {}
};

DbFacade::DbFacade():
    d(new Impl())
{}

DbFacade::~DbFacade()
{}

MissionPtr DbFacade::mission(int id, bool reload)
{
    return d->missionRepository.read(id, reload);
}

MissionItemPtr DbFacade::missionItem(int id, bool reload)
{
    return d->itemRepository.read(id, reload);
}

VehicleDescriptionPtr DbFacade::vehicle(int id, bool reload)
{
    return d->vehicleRepository.read(id, reload);
}

LinkDescriptionPtr DbFacade::link(int id, bool reload)
{
    return d->linkRepository.read(id, reload);
}

MissionAssignmentPtr DbFacade::assignment(int id, bool reload)
{
    return d->assignmentRepository.read(id, reload);
}

bool DbFacade::save(const MissionPtr& mission)
{
    return d->missionRepository.save(mission);
}

bool DbFacade::save(const MissionItemPtr& missionItem)
{
    return d->itemRepository.save(missionItem);
}

bool DbFacade::save(const VehicleDescriptionPtr& vehicle)
{
    return d->vehicleRepository.save(vehicle);
}

bool DbFacade::save(const LinkDescriptionPtr& link)
{
    return d->linkRepository.save(link);
}

bool DbFacade::save(const MissionAssignmentPtr& assignment)
{
    return d->assignmentRepository.save(assignment);
}

bool DbFacade::remove(const MissionPtr& mission)
{
    db::MissionAssignmentPtr assignment = this->missionAssignment(mission->id());
    if (assignment && !this->remove(assignment)) return false;

    for (const MissionItemPtr& item: this->missionItems(mission->id()))
    {
        if (!this->remove(item)) return false;
    }

    return d->missionRepository.remove(mission);
}

bool DbFacade::remove(const MissionItemPtr& missionItem)
{
    return d->itemRepository.remove(missionItem);
}

bool DbFacade::remove(const VehicleDescriptionPtr& vehicle)
{
    db::MissionAssignmentPtr assignment = this->vehicleAssignment(vehicle->id());
    if (assignment && !this->remove(assignment)) return false;

    return d->vehicleRepository.remove(vehicle);
}

bool DbFacade::remove(const LinkDescriptionPtr& link)
{
    return d->linkRepository.remove(link);
}

bool DbFacade::remove(const MissionAssignmentPtr& assignment)
{
    return d->assignmentRepository.remove(assignment);
}

LinkDescriptionPtrList DbFacade::loadLinks(const QString& condition, bool reload)
{
    LinkDescriptionPtrList list;

    for (int id: d->linkRepository.selectId(condition))
    {
        list.append(this->link(id, reload));
    }

    return list;
}

VehicleDescriptionPtrList DbFacade::loadVehicles(const QString& condition, bool reload)
{
    VehicleDescriptionPtrList list;

    for (int id: d->vehicleRepository.selectId(condition))
    {
        list.append(this->vehicle(id, reload));
    }

    return list;
}

MissionPtrList DbFacade::loadMissions(const QString& condition, bool reload)
{
    MissionPtrList list;

    for (int id: d->missionRepository.selectId(condition))
    {
        list.append(this->mission(id, reload));
    }

    return list;
}

MissionItemPtrList DbFacade::loadItems(const QString& condition, bool reload)
{
    MissionItemPtrList list;

    for (int id: d->itemRepository.selectId(condition))
    {
        list.append(this->missionItem(id, reload));
    }
    return list;
}

MissionAssignmentPtr DbFacade::missionAssignment(int missionId)
{
    for (int id: d->assignmentRepository.selectId(
             QString("missionId = %1").arg(missionId)))
    {
        return this->assignment(id);
    }
    return MissionAssignmentPtr();
}

MissionAssignmentPtr DbFacade::vehicleAssignment(int vehicleId)
{
    for (int id: d->assignmentRepository.selectId(
             QString("vehicleId = %1").arg(vehicleId)))
    {
        return this->assignment(id);
    }
    return MissionAssignmentPtr();
}

MissionItemPtrList DbFacade::missionItems()
{
    return this->loadItems();
}

MissionItemPtrList DbFacade::missionItems(int missionId)
{
    return this->loadItems(QString("missionId = %1 ORDER BY sequence").arg(
                               missionId));
}

MissionItemPtr DbFacade::missionItem(int missionId, int sequence)
{
    for (int id: d->itemRepository.selectId(
             QString("missionId = %1 AND sequence = %2").arg(
                 missionId).arg(sequence)))
    {
        return this->missionItem(id);
    }
    return MissionItemPtr();
}
