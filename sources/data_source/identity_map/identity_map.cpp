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
    QHash<int, Mission*> missions;
    QHash<int, MissionItem*> missionItems;

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

Mission* IdentityMap::mission(int id)
{
    if (d->missions.contains(id)) return d->missions[id];

    Mission* entity = d->missionRepository.read(id);
    if (entity) d->missions[id] = entity;
    return entity;
}

MissionItem* IdentityMap::missionItem(int id)
{
    if (d->missionItems.contains(id)) return d->missionItems[id];

    MissionItem* entity = d->missionItemRepository.read(id);
    if (entity) d->missionItems[id] = entity;
    return entity;
}
