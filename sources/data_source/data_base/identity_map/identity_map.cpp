#include "identity_map.h"

// Qt
#include <QHash>

// Internal
#include "generic_repository.h"
#include "generic_repository_impl.h"

#include "mission.h"
#include "mission_item.h"
#include "vehicle.h"

using namespace data_source;

class IdentityMap::Impl
{
public:
    QHash<int, MissionPtr> missions;
    QHash<int, MissionItemPtr> missionItems;
    QHash<int, VehiclePtr> vehicles;

    GenericRepository<Mission> missionRepository;
    GenericRepository<MissionItem> missionItemRepository;
    GenericRepository<Vehicle> vehicleRepository;
};

IdentityMap::IdentityMap():
    d(new Impl())
{}

IdentityMap::~IdentityMap()
{
    delete d;
}

MissionPtr IdentityMap::readMission(int id, bool reload)
{
    bool contains = d->missions.contains(id);
    if (!contains) d->missions[id] = MissionPtr::create(id);

    if (!contains || reload)
    {
        // TODO: handle if read fails
        d->missionRepository.read(d->missions[id].data());

        auto ids = d->missionItemRepository.selectId(
                       QString("missionId = %1 ORDER BY sequence").arg(id));
        d->missions[id]->setCount(ids.count());

        for (int itemId : ids)
        {
            MissionItemPtr item = this->readMissionItem(itemId, reload);
            if (item) d->missions[id]->setItem(item->sequence(), item);
        }
    }

    return d->missions[id];
}

MissionItemPtr IdentityMap::readMissionItem(int id, bool reload)
{
    bool contains = d->missionItems.contains(id);
    if (!contains) d->missionItems[id] = MissionItemPtr::create(id);

    if (!contains || reload)
    {
        d->missionItemRepository.read(d->missionItems[id].data());
    }

    return d->missionItems[id];
}

VehiclePtr IdentityMap::readVehicle(int id, bool reload)
{
    bool contains = d->vehicles.contains(id);
    if (!contains) d->vehicles[id] = VehiclePtr::create(id);

    if (!contains || reload)
    {
        d->vehicleRepository.read(d->vehicles[id].data());
    }

    return d->vehicles[id];
}

bool IdentityMap::save(const MissionPtr& mission)
{
    // TODO: db transaction
    if (mission->id() > 0)
    {
        if (!d->missionRepository.update(mission.data())) return false;
    }
    else
    {
        if (!d->missionRepository.insert(mission.data())) return false;

        for (const MissionItemPtr& item: mission->items())
            item->setMissionId(mission->id());
    }

    for (const MissionItemPtr& item: mission->items())
    {
        if (!this->save(item)) return false;
    }

    d->missions[mission->id()] = mission;
    return true;
}

bool IdentityMap::save(const MissionItemPtr& missionItem)
{
    if (missionItem->id() > 0)
    {
        if (!d->missionItemRepository.update(missionItem.data())) return false;
    }
    else
    {
        if (!d->missionItemRepository.insert(missionItem.data())) return false;
    }

    d->missionItems[missionItem->id()] = missionItem;
    return true;
}

bool IdentityMap::save(const VehiclePtr& vehicle)
{
    if (vehicle->id() > 0)
    {
        if (!d->vehicleRepository.update(vehicle.data())) return false;
    }
    else
    {
        if (!d->vehicleRepository.insert(vehicle.data())) return false;
    }

    d->vehicles[vehicle->id()] = vehicle;
    return true;
}

bool IdentityMap::remove(const MissionPtr& mission)
{
    for (const MissionItemPtr& item: mission->items())
    {
        if (!this->remove(item)) return false;
    }

    this->unload(mission);
    mission->setId(0);
    return d->missionRepository.remove(mission.data());
}

bool IdentityMap::remove(const MissionItemPtr& missionItem)
{
    this->unload(missionItem);
    missionItem->setId(0);
    return d->missionItemRepository.remove(missionItem.data());
}

bool IdentityMap::remove(const VehiclePtr& vehicle)
{
    this->unload(vehicle);
    return d->vehicleRepository.remove(vehicle.data());
}

void IdentityMap::unload(const MissionPtr& mission)
{
    for (const MissionItemPtr& item: mission->items())
        this->unload(item);

    d->missions.remove(mission->id());
}

void IdentityMap::unload(const MissionItemPtr& missionItem)
{
    d->missionItems.remove(missionItem->id());
}

void IdentityMap::unload(const VehiclePtr& vehicle)
{
    d->vehicles.remove(vehicle->id());
}
