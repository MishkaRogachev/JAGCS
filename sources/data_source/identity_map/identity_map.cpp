#include "identity_map.h"

// Qt
#include <QHash>

// Internal
#include "mission_repository.h"
#include "mission_item_repository.h"

using namespace data_source;

class IdentityMap::Impl
{
public:
    QHash<int, MissionPtr> missions;
    QHash<int, MissionItemPtr> missionItems;

    MissionRepository missionRepository;
    MissionItemRepository missionItemRepository;
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

    MissionPtr entity(d->missionRepository.read(id));
    if (entity) d->missions[id] = entity;
    return entity;
}

MissionItemPtr IdentityMap::missionItem(int id)
{
    if (d->missionItems.contains(id)) return d->missionItems[id];

    MissionItemPtr entity(d->missionItemRepository.read(id));
    if (entity) d->missionItems[id] = entity;
    return entity;
}

MissionPtr IdentityMap::createMission()
{
    MissionPtr entity(new Mission());
    if (!d->missionRepository.insert(entity.data())) return MissionPtr();

    d->missions[entity->id()] = entity;
    return entity;
}

MissionItemPtr IdentityMap::createMissionItem(const MissionPtr& mission)
{
    MissionItemPtr entity(new MissionItem());
    entity->setMissionId(mission->id());
    if (!d->missionItemRepository.insert(entity.data())) return MissionItemPtr();

    d->missionItems[entity->id()] = entity;
    return entity;
}

void IdentityMap::saveMission(const MissionPtr& mission)
{
    d->missionRepository.update(mission.data());
}

void IdentityMap::saveMissionItem(const MissionItemPtr& missionItem)
{
    d->missionItemRepository.update(missionItem.data());
}

void IdentityMap::removeMission(const MissionPtr& mission)
{
    d->missions.remove(mission->id());
    d->missionRepository.remove(mission.data());
}

void IdentityMap::removeMissionItem(const MissionItemPtr& missionItem)
{
    d->missionItems.remove(missionItem->id());
    d->missionItemRepository.remove(missionItem.data());
}

void IdentityMap::clear()
{
    d->missions.clear();
    d->missionItems.clear();
}
