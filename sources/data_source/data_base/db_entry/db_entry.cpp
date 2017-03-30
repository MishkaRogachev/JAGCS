#include "db_entry.h"

// Qt
#include <QDebug>

// Internal
#include "generic_repository.h"
#include "generic_repository_impl.h"

#include "mission.h"
#include "mission_item.h"
#include "vehicle.h"

using namespace data_source;

class DbEntry::Impl
{
public:
    GenericRepository<Mission> missionRepository;
    GenericRepository<MissionItem> missionItemRepository;
    GenericRepository<Vehicle> vehicleRepository;

    Impl():
        missionRepository("missions"),
        missionItemRepository("mission_items"),
        vehicleRepository("vehicles")
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

VehiclePtr DbEntry::readVehicle(int id, bool reload)
{
    return d->vehicleRepository.read(id, reload);
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

bool DbEntry::save(const VehiclePtr& vehicle)
{
    return d->vehicleRepository.save(vehicle);
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

bool DbEntry::remove(const VehiclePtr& vehicle)
{
    return d->vehicleRepository.remove(vehicle);
}

void DbEntry::unload(const MissionPtr& mission)
{
    for (const MissionItemPtr& item: mission->items())
        this->unload(item);

    d->missionRepository.unload(mission->id());
}

void DbEntry::unload(const MissionItemPtr& missionItem)
{
    d->missionItemRepository.unload(missionItem->id());
}

void DbEntry::unload(const VehiclePtr& vehicle)
{
    d->vehicleRepository.unload(vehicle->id());
}

