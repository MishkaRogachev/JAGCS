#include "db_entry.h"

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

class DbEntry::Impl
{
public:
    GenericRepository<Mission> missionRepository;
    GenericRepository<MissionItem> missionItemRepository;
    GenericRepository<VehicleDescription> vehicleRepository;
    GenericRepository<MissionAssignment> assignmentsRepository;
    GenericRepository<LinkDescription> linkRepository;

    Impl():
        missionRepository("missions"),
        missionItemRepository("mission_items"),
        vehicleRepository("vehicles"),
        assignmentsRepository("mission_assignments"),
        linkRepository("links")
    {}
};

DbEntry::DbEntry():
    d(new Impl())
{}

DbEntry::~DbEntry()
{}

MissionPtr DbEntry::readMission(int id, bool reload)
{
    bool loadItems = !d->missionRepository.contains(id) || reload;
    MissionPtr mission = d->missionRepository.read(id, reload);
    if (loadItems)
    {
        mission->clearItems();
        QList<int> itemIds = d->missionItemRepository.selectId(
                           QString("missionId = %1 ORDER BY sequence").arg(id));

        mission->setCount(itemIds.count());

        for (int itemId : itemIds)
        {
            MissionItemPtr item = this->readMissionItem(itemId, reload);
            if (item) mission->setItem(item->sequence(), item);
        }
    }

    return mission;
}

MissionItemPtr DbEntry::readMissionItem(int id, bool reload)
{
    return d->missionItemRepository.read(id, reload);
}

VehicleDescriptionPtr DbEntry::readVehicle(int id, bool reload)
{
    return d->vehicleRepository.read(id, reload);
}

LinkDescriptionPtr DbEntry::readLink(int id, bool reload)
{
    return d->linkRepository.read(id, reload);
}

MissionAssignmentPtr DbEntry::readAssignment(int id, bool reload)
{
    return d->assignmentsRepository.read(id, reload);
}

bool DbEntry::save(const MissionPtr& mission)
{
    // TODO: db transaction
    if (!d->missionRepository.save(mission)) return false;

    for (const MissionItemPtr& item: mission->items())
    {
        if (!this->save(item)) return false;
    }

    return true;
}

bool DbEntry::save(const MissionItemPtr& missionItem)
{
    return d->missionItemRepository.save(missionItem);
}

bool DbEntry::save(const VehicleDescriptionPtr& vehicle)
{
    return d->vehicleRepository.save(vehicle);
}

bool DbEntry::save(const LinkDescriptionPtr& link)
{
    return d->linkRepository.save(link);
}

bool DbEntry::save(const MissionAssignmentPtr& assignment)
{
    return d->assignmentsRepository.save(assignment);
}

bool DbEntry::remove(const MissionPtr& mission)
{
    for (const MissionItemPtr& item: mission->items())
    {
        if (!this->remove(item)) return false;
    }

    return d->missionRepository.remove(mission);
}

bool DbEntry::remove(const MissionItemPtr& missionItem)
{
    return d->missionItemRepository.remove(missionItem);
}

bool DbEntry::remove(const VehicleDescriptionPtr& vehicle)
{
    return d->vehicleRepository.remove(vehicle);
}

bool DbEntry::remove(const LinkDescriptionPtr& link)
{
    return d->linkRepository.remove(link);
}

bool DbEntry::remove(const MissionAssignmentPtr& assignment)
{
    return d->assignmentsRepository.remove(assignment);
}

LinkDescriptionPtrList DbEntry::loadLinks()
{
    LinkDescriptionPtrList list;

    for (int id: d->linkRepository.selectId())
    {
        list.append(this->readLink(id));
    }

    return list;
}

VehicleDescriptionPtrList DbEntry::loadVehicles()
{
    VehicleDescriptionPtrList list;

    for (int id: d->vehicleRepository.selectId())
    {
        list.append(this->readVehicle(id));
    }

    return list;
}

MissionPtrList DbEntry::loadMissions()
{
    MissionPtrList list;

    for (int id: d->missionRepository.selectId())
    {
        list.append(this->readMission(id));
    }

    return list;
}

MissionAssignmentPtr DbEntry::missionAssignment(int missionId)
{
    for (int id: d->assignmentsRepository.selectId(
             QString("missionId = %1").arg(missionId)))
    {
        return this->readAssignment(id);
    }
    return MissionAssignmentPtr();
}

MissionAssignmentPtr DbEntry::vehicleAssignment(int vehicleId)
{
    for (int id: d->assignmentsRepository.selectId(
             QString("vehicleId = %1").arg(vehicleId)))
    {
        return this->readAssignment(id);
    }
    return MissionAssignmentPtr();
}
