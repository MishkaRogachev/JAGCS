#include "vehicle_service.h"

// Qt
#include <QMutexLocker>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "vehicle.h"

#include "generic_repository.h"

#include "mission_service.h"

using namespace dto;
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
    qRegisterMetaType<dto::VehiclePtr>("dto::VehiclePtr");

    d->missionService = missionService;
    connect(this, &VehicleService::vehicleChanged, missionService,
            &MissionService::onVehicleChanged);

    d->loadVehicles();
}

VehicleService::~VehicleService()
{}

VehiclePtr VehicleService::vehicle(int vehicleId) const
{
    QMutexLocker locker(&d->mutex);

    if (vehicleId) return d->vehicleRepository.read(vehicleId);
    return VehiclePtr();
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

    if (isNew)
    {
        settings::Provider::setValue(settings::vehicle::vehicle + QString::number(vehicle->id()) +
                                     "/" + settings::vehicle::instruments::status +
                                     "/" + settings::visibility, true);
        settings::Provider::setValue(settings::vehicle::vehicle + QString::number(vehicle->id()) +
                                     "/" + settings::vehicle::instruments::fd +
                                     "/" + settings::visibility, true);
        settings::Provider::setValue(settings::vehicle::vehicle + QString::number(vehicle->id()) +
                                     "/" + settings::vehicle::instruments::hsi +
                                     "/" + settings::visibility, true);
        emit vehicleAdded(vehicle);
    }
    else
    {
        emit vehicleChanged(vehicle);
    }

    return true;
}

bool VehicleService::remove(const VehiclePtr& vehicle)
{
    QMutexLocker locker(&d->mutex);
    // FIXME: crash on removing active vehicle
    MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicle->id());
    if (assignment && !d->missionService->remove(assignment)) return false;

    if (!d->vehicleRepository.remove(vehicle)) return false;

    settings::Provider::remove(settings::vehicle::vehicle + QString::number(vehicle->id()));

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
    vehicle->setName(tr("MAV %1").arg(mavId));
    vehicle->setType(Vehicle::Auto);

    return this->save(vehicle);
}
