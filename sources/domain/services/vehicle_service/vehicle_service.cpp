#include "vehicle_service.h"

// Qt
#include <QMutexLocker>
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
    QMutex mutex;
    GenericRepository<Vehicle> vehicleRepository;
    MissionService* missionService;

    Impl():
        mutex(QMutex::Recursive),
        vehicleRepository("vehicles")
    {}

    void loadVehicles(const QString& condition = QString())
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

    d->loadVehicles();
}

VehicleService::~VehicleService()
{}

VehiclePtr VehicleService::vehicle(int vehicleId) const
{
    QMutexLocker locker(&d->mutex);

    return d->vehicleRepository.read(vehicleId);
}

VehiclePtrList VehicleService::vehicles() const
{
    QMutexLocker locker(&d->mutex);

    return d->vehicleRepository.loadedEntities();
}

int VehicleService::vehicleIdByMavId(int mavId) const
{
    QMutexLocker locker(&d->mutex);

    for (const VehiclePtr& vehicle: d->vehicleRepository.loadedEntities())
    {
        if (vehicle->mavId() == mavId) return vehicle->id();
    }
    return 0;
}

int VehicleService::mavIdByVehicleId(int vehicleId) const
{
    QMutexLocker locker(&d->mutex);

    VehiclePtr vehicle = this->vehicle(vehicleId);
    if (vehicle) return vehicle->mavId();
    return -1;
}

QList<int> VehicleService::employedMavIds() const
{
    QList<int> mavIds;
    for (const VehiclePtr& vehicle: this->vehicles())
    {
        mavIds.append(vehicle->mavId());
    }
    return mavIds;
}

bool VehicleService::save(const VehiclePtr& vehicle)
{
    QMutexLocker locker(&d->mutex);

    bool isNew = vehicle->id() == 0;
    if (!d->vehicleRepository.save(vehicle)) return false;

    emit (isNew ? vehicleAdded(vehicle) : vehicleChanged(vehicle));
    return true;
}

bool VehicleService::remove(const VehiclePtr& vehicle)
{
    QMutexLocker locker(&d->mutex);
    // FIXME: crash on removing active vehicle
    MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicle->id());
    if (assignment && !d->missionService->remove(assignment)) return false;

    if (!d->vehicleRepository.remove(vehicle)) return false;
    emit vehicleRemoved(vehicle);
    return true;
}

bool VehicleService::addNewVehicle()
{
    VehiclePtr vehicle = VehiclePtr::create();

    QList<int> mavIds = this->employedMavIds();
    int mavId = 1;
    while (mavIds.contains(mavId)) mavId++;

    vehicle->setMavId(mavId);
    vehicle->setName(tr("New vehicle"));
    vehicle->setType(Vehicle::Auto);

    return this->save(vehicle);
}
