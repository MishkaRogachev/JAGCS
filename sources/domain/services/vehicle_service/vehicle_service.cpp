#include "vehicle_service.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle.h"

#include "generic_repository.h"
#include "generic_repository_impl.h"

#include "mission_service.h"

using namespace dao;
using namespace domain;

class VehicleService::Impl
{
public:
    GenericRepository<Vehicle> vehicleRepository;
    MissionService* missionService;

    Impl():
        vehicleRepository("vehicles")
    {}
};

VehicleService::VehicleService(MissionService* missionService, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->missionService = missionService;
}

VehicleService::~VehicleService()
{}

VehiclePtr VehicleService::vehicle(int id, bool reload)
{
    return d->vehicleRepository.read(id, reload);
}

VehiclePtrList VehicleService::vehicles(const QString& condition, bool reload)
{
    VehiclePtrList list;

    for (int id: d->vehicleRepository.selectId(condition))
    {
        list.append(this->vehicle(id, reload));
    }

    return list;
}

int VehicleService::vehicleIdByMavId(int mavId)
{
    for (int id: d->vehicleRepository.selectId(QString("mavId = %1").arg(mavId)))
        return id;
    return 0;
}

int VehicleService::mavIdByVehicleId(int id)
{
    VehiclePtr vehicle = this->vehicle(id);
    if (vehicle) return vehicle->mavId();
    return -1;
}

bool VehicleService::save(const VehiclePtr& vehicle)
{
    bool isNew = vehicle->id() == 0;
    if (!d->vehicleRepository.save(vehicle)) return false;

    emit (isNew ? vehicleAdded(vehicle) : vehicleChanged(vehicle));
    return true;
}

bool VehicleService::remove(const VehiclePtr& vehicle)
{
    MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicle->id());
    if (assignment && !d->missionService->remove(assignment)) return false;

    if (!d->vehicleRepository.remove(vehicle)) return false;
    emit vehicleRemoved(vehicle);
    return true;
}
