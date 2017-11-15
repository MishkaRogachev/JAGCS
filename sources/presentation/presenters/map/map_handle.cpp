#include "map_handle.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "mission_service.h"

#include "mission.h"
#include "mission_item.h"

using namespace presentation;

class MapHandle::Impl
{
public:
    domain::MissionService* const service = domain::ServiceRegistry::missionService();

    dao::MissionPtr mission;
    dao::MissionItemPtr item;
};

MapHandle::MapHandle(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

MapHandle::~MapHandle()
{}

dao::MissionPtr MapHandle::selectedMission() const
{
    return d->mission;
}

dao::MissionItemPtr MapHandle::selectedMissionItem() const
{
    return d->item;
}

void MapHandle::selectMission(const dao::MissionPtr& mission)
{
    if (d->mission == mission) return;

    d->mission = mission;
    emit missionSelected(mission);

    if (mission.isNull() || (d->item && d->item->missionId() != mission->id()))
    {
        d->item.clear();
        emit missionItemSelected(d->item);
    }
}

void MapHandle::selectMissionItem(const dao::MissionItemPtr& item)
{
    if (d->item == item) return;

    d->item = item;
    emit missionItemSelected(item);

    if (item)
    {
        if (d->mission.isNull() || d->mission->id() != item->missionId())
        {
            d->mission = d->service->mission(item->missionId());
            emit missionSelected(d->mission);
        }
    }
    else if (d->mission)
    {
        d->mission.clear();
        emit missionSelected(d->mission);
    }
}
