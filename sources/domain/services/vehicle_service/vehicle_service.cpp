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

class VehicleService::Impl // FIXME : make service sync db on create, destroy and by request
{
public:
    GenericRepository<Vehicle> vehicleRepository;
    MissionService* missionService;

    Impl():
        vehicleRepository("vehicles")
    {}

    void load(const QString& condition = QString())
    {
        for (int id: vehicleRepository.selectId(condition)) vehicleRepository.read(id);
    }
};

VehicleService::VehicleService(MissionService* missionService, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    qRegisterMetaType<dao::VehiclePtr>("dao::VehiclePtr");

    d->missionService = missionService;
    d->load();
}

VehicleService::~VehicleService()
{}

VehiclePtr VehicleService::vehicle(int id)
{
    return d->vehicleRepository.read(id, false);
}

VehiclePtrList VehicleService::vehicles()
{
    return d->vehicleRepository.loadedEntities();
}

int VehicleService::vehicleIdByMavId(int mavId)
{
    for (const VehiclePtr& vehicle: d->vehicleRepository.loadedEntities())
    {
        if (vehicle->mavId() == mavId) return vehicle->id();
    }

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
