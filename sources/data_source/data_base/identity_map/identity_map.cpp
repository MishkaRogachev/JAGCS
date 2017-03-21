#include "identity_map.h"

// Qt
#include <QHash>

// Internal
#include "generic_repository.h"
#include "generic_repository_impl.h"

#include "mission.h"
#include "mission_item.h"

using namespace data_source;

class IdentityMap::Impl
{
public:
    QHash<int, MissionPtr> missions;
    QHash<int, MissionItemPtr> missionItems;

    GenericRepository<Mission> missionRepository;
    GenericRepository<MissionItem> missionItemRepository;
};

IdentityMap::IdentityMap():
    d(new Impl())
{}

IdentityMap::~IdentityMap()
{
    delete d;
}

MissionPtr IdentityMap::mission(int id)
{
    if (d->missions.contains(id)) return d->missions[id];

    MissionPtr mission(d->missionRepository.read(id, this));
    if (mission)
    {
        d->missions[id] = mission;

        auto items = d->missionItemRepository.selectId(
                         QString("missionId = %1 ORDER BY sequence").arg(id));
        for (int id : items)
        {
            MissionItemPtr item = this->missionItem(id);
            if (item) mission->appendItem(item);
        }
    }
    return mission;
}

MissionItemPtr IdentityMap::missionItem(int id)
{
    if (d->missionItems.contains(id)) return d->missionItems[id];

    MissionItemPtr entity(d->missionItemRepository.read(id, this));
    if (entity)
    {
        d->missionItems[id] = entity;
    }
    return entity;
}

MissionPtr IdentityMap::createMission()
{
    MissionPtr entity(new Mission(this));
    if (!d->missionRepository.insert(entity.data())) return MissionPtr();

    d->missions[entity->id()] = entity;
    return entity;
}

MissionItemPtr IdentityMap::createMissionItem(const MissionPtr& mission)
{
    MissionItemPtr missionItem(new MissionItem(this));
    missionItem->setMissionId(mission->id());

    if (!d->missionItemRepository.insert(missionItem.data()))
    {
        return MissionItemPtr();
    }

    d->missionItems[missionItem->id()] = missionItem;
    return missionItem;
}

void IdentityMap::saveMission(const MissionPtr& mission)
{
    d->missionRepository.update(mission.data());
}

void IdentityMap::saveMissionAll(const MissionPtr& mission)
{
    this->saveMission(mission);

    for (const MissionItemPtr& item: mission->items())
        this->saveMissionItem(item);
}

void IdentityMap::saveMissionItem(const MissionItemPtr& missionItem)
{
    d->missionItemRepository.update(missionItem.data());
}

void IdentityMap::removeMission(const MissionPtr& mission)
{
    for (const MissionItemPtr& item: mission->items())
        this->removeMissionItem(item);

    this->unloadMission(mission);
    d->missionRepository.remove(mission.data());
}

void IdentityMap::removeMissionItem(const MissionItemPtr& missionItem)
{
    this->unloadMissionItem(missionItem);
    d->missionItemRepository.remove(missionItem.data());
}

void IdentityMap::unloadMission(const MissionPtr& mission)
{
    for (const MissionItemPtr& item: mission->items())
        this->unloadMissionItem(item);

    d->missions.remove(mission->id());
}

void IdentityMap::unloadMissionItem(const MissionItemPtr& missionItem)
{
    d->missionItems.remove(missionItem->id());
}
