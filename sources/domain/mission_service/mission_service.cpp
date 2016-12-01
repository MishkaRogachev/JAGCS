#include "mission_service.h"

// Qt
#include <QMap>

// Internal
#include "mission.h"

using namespace domain;

class MissionService::Impl
{
public:
    QMap<uint8_t, Mission*> missions;
};

MissionService::MissionService(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

MissionService::~MissionService()
{
    delete d;
}

Mission* MissionService::mission(uint8_t id) const
{
    return d->missions.value(id, nullptr);
}

uint8_t MissionService::missionId(Mission* mission) const
{
    return d->missions.key(mission);
}

QList<Mission*> MissionService::missions() const
{
    return d->missions.values();
}

QList<uint8_t> MissionService::missionIds() const
{
    return d->missions.keys();
}

Mission* MissionService::requestMission(uint8_t id)
{
    if (!d->missions.contains(id))
    {
        d->missions[id] = new Mission(this);
        emit missionAdded(id);
    }

    return d->missions[id];
}

void MissionService::removeMission(uint8_t id)
{
    if (!d->missions.contains(id)) return;

    d->missions.remove(id);
    emit missionRemoved(id);
}
