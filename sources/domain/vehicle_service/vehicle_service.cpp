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
{
    qRegisterMetaType<Attitude>("Attitude");
    qRegisterMetaType<Position>("Navigation");
    qRegisterMetaType<Gps>("Gps");
    qRegisterMetaType<PowerSystem>("PowerSystem");
}

VehicleService::~VehicleService()
{
    while (!d->vehicles.isEmpty())
        this->removeVehicle(d->vehicles.keys().first());

    delete d;
}

Vehicle* VehicleService::vehicle(uint8_t id) const
{
    return d->vehicles.value(id, nullptr);
}

uint8_t VehicleService::vehicleId(Vehicle* vehicle) const
{
    return d->vehicles.key(vehicle);
}

QList<Vehicle*> VehicleService::vehicles() const
{
    return d->vehicles.values();
}

QList<uint8_t> VehicleService::vehicleIds() const
{
    return d->vehicles.keys();
}

Vehicle* VehicleService::forceVehicle(uint8_t id)
{
    if (!d->vehicles.contains(id))
    {
        d->vehicles[id] = new Vehicle(id, this);
        emit vehicleAdded(d->vehicles[id]);
    }

    return d->vehicles[id];
}

void VehicleService::removeVehicle(uint8_t id)
{
    Vehicle* vehicle = d->vehicles.take(id);
    emit vehicleRemoved(vehicle);
}

void VehicleService::deleteVehicle(uint8_t id)
{
    Vehicle* vehicle = d->vehicles.value(id, nullptr);
    if (!vehicle) return;

    this->removeVehicle(id);
    vehicle->deleteLater();
}
