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

DbFacade::DbFacade():
    d(new Impl())
{}

DbFacade::~DbFacade()
{}

MissionPtr DbFacade::readMission(int id, bool reload)
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

MissionItemPtr DbFacade::readMissionItem(int id, bool reload)
{
    return d->missionItemRepository.read(id, reload);
}

VehicleDescriptionPtr DbFacade::readVehicle(int id, bool reload)
{
    return d->vehicleRepository.read(id, reload);
}

LinkDescriptionPtr DbFacade::readLink(int id, bool reload)
{
    return d->linkRepository.read(id, reload);
}

MissionAssignmentPtr DbFacade::readAssignment(int id, bool reload)
{
    return d->assignmentsRepository.read(id, reload);
}

bool DbFacade::save(const MissionPtr& mission)
{
    // TODO: db transaction
    if (!d->missionRepository.save(mission)) return false;

    for (const MissionItemPtr& item: mission->items())
    {
        if (!this->save(item)) return false;
    }

    return true;
}

bool DbFacade::save(const MissionItemPtr& missionItem)
{
    return d->missionItemRepository.save(missionItem);
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
    return d->assignmentsRepository.save(assignment);
}

bool DbFacade::remove(const MissionPtr& mission)
{
    db::MissionAssignmentPtr assignment = this->missionAssignment(mission->id());
    if (!assignment.isNull()) this->remove(assignment);

    for (const MissionItemPtr& item: mission->items())
    {
        if (!this->remove(item)) return false;
    }

    return d->missionRepository.remove(mission);
}

bool DbFacade::remove(const MissionItemPtr& missionItem)
{
    return d->missionItemRepository.remove(missionItem);
}

bool DbFacade::remove(const VehicleDescriptionPtr& vehicle)
{
    return d->vehicleRepository.remove(vehicle);
}

bool DbFacade::remove(const LinkDescriptionPtr& link)
{
    return d->linkRepository.remove(link);
}

bool DbFacade::remove(const MissionAssignmentPtr& assignment)
{
    return d->assignmentsRepository.remove(assignment);
}

LinkDescriptionPtrList DbFacade::loadLinks()
{
    LinkDescriptionPtrList list;

    for (int id: d->linkRepository.selectId())
    {
        list.append(this->readLink(id));
    }

    return list;
}

VehicleDescriptionPtrList DbFacade::loadVehicles()
{
    VehicleDescriptionPtrList list;

    for (int id: d->vehicleRepository.selectId())
    {
        list.append(this->readVehicle(id));
    }

    return list;
}

MissionPtrList DbFacade::loadMissions()
{
    MissionPtrList list;

    for (int id: d->missionRepository.selectId())
    {
        list.append(this->readMission(id));
    }

    return list;
}

MissionAssignmentPtr DbFacade::missionAssignment(int missionId)
{
    for (int id: d->assignmentsRepository.selectId(
             QString("missionId = %1").arg(missionId)))
    {
        return this->readAssignment(id);
    }
    return MissionAssignmentPtr();
}

MissionAssignmentPtr DbFacade::vehicleAssignment(int vehicleId)
{
    for (int id: d->assignmentsRepository.selectId(
             QString("vehicleId = %1").arg(vehicleId)))
    {
        return this->readAssignment(id);
    }
    return MissionAssignmentPtr();
}
