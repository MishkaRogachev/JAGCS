#include "mission_service.h"

// Internal
#include "db_entry.h"

#include "mission.h"
#include "mission_item.h"

using namespace db;
using namespace domain;

class MissionService::Impl
{
public:
    DbEntry* entry;

    MissionPtrList missions;
};

MissionService::MissionService(db::DbEntry* entry, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->entry = entry;

    d->missions = entry->loadMissions();
}

MissionService::~MissionService()
{
    for (const MissionPtr& mission: d->missions)
    {
        d->entry->save(mission);
    }
}

MissionPtrList MissionService::missions() const
{
    return d->missions;
}

MissionPtr MissionService::findMissionByName(const QString& name) const
{
    for (const MissionPtr& mission: d->missions)
    {
        if (mission->name() == name) return mission;
    }
    return MissionPtr();
}

void MissionService::saveMission(const MissionPtr& mission)
{
    if (!d->entry->save(mission)) return;

    if (!d->missions.contains(mission))
    {
        d->missions.append(mission);
        emit missionAdded(mission);
    }
}

void MissionService::removeMission(const MissionPtr& mission)
{
    if (!d->entry->remove(mission)) return;

    d->missions.removeOne(mission);
    emit missionRemoved(mission);
}

void MissionService::saveMissionItem(const MissionItemPtr& item)
{
    bool isNew = item->id() == 0;

    if (!d->entry->save(item)) return;
    if (isNew) emit missionItemAdded(item);
}

void MissionService::removeMissionItem(const MissionItemPtr& item)
{
    if (!d->entry->remove(item)) return;
    emit missionItemRemoved(item);
}
