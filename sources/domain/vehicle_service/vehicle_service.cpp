#include "vehicle_service.h"

// Qt
#include <QMap>

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
    return d->vehicles.value(id);
}

uint8_t VehicleService::vehileId(Vehicle* vehicle) const
{
    return d->vehicles.key(vehicle);
}

void VehicleService::removeVehicle(uint8_t id)
{
    d->vehicles.remove(id);
}
