#include "mission_service.h"

// Qt
#include <QDebug>

// Internal
#include "db_facade.h"

#include "mission.h"
#include "mission_item.h"
#include "mission_assignment.h"
#include "vehicle_description.h"

using namespace db;
using namespace domain;

class MissionService::Impl
{
public:
    DbFacade* facade;
};

MissionService::MissionService(db::DbFacade* facade, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->facade = facade;

    connect(facade, &DbFacade::missionAdded, this, &MissionService::missionAdded);
    connect(facade, &DbFacade::missionRemoved, this, &MissionService::missionRemoved);
    connect(facade, &DbFacade::missionChanged, this, &MissionService::missionChanged);

    connect(facade, &DbFacade::missionItemAdded, this, &MissionService::missionItemAdded);
    connect(facade, &DbFacade::missionItemRemoved, this, &MissionService::missionItemRemoved);
    connect(facade, &DbFacade::missionItemChanged, this, &MissionService::missionItemChanged);

    connect(facade, &DbFacade::assignmentAdded, this, &MissionService::assignmentAdded);
    connect(facade, &DbFacade::assignmentRemoved, this, &MissionService::assignmentRemoved);
    connect(facade, &DbFacade::assignmentChanged, this, &MissionService::assignmentChanged);
}

MissionService::~MissionService()
{}

MissionPtrList MissionService::missions() const
{
    return d->facade->loadMissions();;
}

MissionPtr MissionService::mission(int id) const
{
    return d->facade->mission(id);
}

MissionAssignmentPtr MissionService::missionAssignment(const MissionPtr& mission) const
{
    return d->facade->missionAssignment(mission->id());
}

MissionAssignmentPtr MissionService::vehicleAssignment(const VehicleDescriptionPtr& vehicle) const
{
    return d->facade->vehicleAssignment(vehicle->id());
}

void MissionService::assign(const MissionPtr& mission, const VehicleDescriptionPtr& vehicle)
{
    d->facade->assign(mission->id(), vehicle->id());
}

void MissionService::unassign(const MissionPtr& mission)
{
    d->facade->unassign(mission->id());
}

MissionItemPtrList MissionService::missionItems() const
{
    return d->facade->missionItems();
}

MissionItemPtrList MissionService::missionItems(int missionId) const
{
    return d->facade->missionItems(missionId);
}

MissionItemPtr MissionService::missionItem(int missionId, int sequence) const
{
    return d->facade->missionItem(missionId, sequence);
}

void MissionService::saveMission(const MissionPtr& mission)
{
    d->facade->save(mission);
}

void MissionService::removeMission(const MissionPtr& mission)
{
    d->facade->remove(mission);
}

void MissionService::saveMissionItem(const MissionItemPtr& item)
{
    d->facade->save(item);
}

void MissionService::removeMissionItem(const MissionItemPtr& item)
{
    d->facade->remove(item);
}

void MissionService::addNewMissionItem(int missionId)
{
    d->facade->addNewMissionItem(missionId);
}

void MissionService::saveMissionItems(int missionId)
{
    d->facade->saveMissionItems(missionId);
}
