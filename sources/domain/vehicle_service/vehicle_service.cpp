#include "vehicle_service.h"

// Qt
#include <QMap>

// Internal
#include "vehicle.h"

using namespace domain;

class VehicleService::Impl
{
public:
    QMap<uint8_t, Vehicle*> vehicles;
};

VehicleService::VehicleService(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

VehicleService::~VehicleService()
{
    delete d;
}

Vehicle* VehicleService::vehicle(uint8_t id) const
{
    return d->vehicles.value(id, nullptr);
}

uint8_t VehicleService::vehileId(Vehicle* vehicle) const
{
    return d->vehicles.key(vehicle);
}

QList<Vehicle*> VehicleService::vehicles() const
{
    return d->vehicles.values();
}

Vehicle*VehicleService::requestVehicle(uint8_t id)
{
    return d->vehicles[id];
}

void VehicleService::forgetVehicle(uint8_t id)
{
    d->vehicles.remove(id);
}
