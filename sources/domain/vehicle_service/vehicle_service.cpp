#include "vehicle_service.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle.h"

using namespace domain;

VehicleService::VehicleService(QObject* parent):
    QObject(parent)
{
    qRegisterMetaType<Attitude>("Attitude");
    qRegisterMetaType<Position>("Navigation");
    qRegisterMetaType<Gps>("Gps");
    qRegisterMetaType<PowerSystem>("PowerSystem");
}

Vehicle* VehicleService::vehicle(int index) const
{
    return m_vehicles.at(index);
}

const QList<Vehicle*>& VehicleService::vehicles() const
{
    return m_vehicles;
}

Vehicle* VehicleService::forceVehicle(uint8_t id)
{
    for (domain::Vehicle* vehicle: m_vehicles)
    {
        if (vehicle->vehicleId() == id) return vehicle;
    }

    this->addVehicle(new Vehicle(id, this));
    return m_vehicles.last();
}

void VehicleService::addVehicle(Vehicle* vehicle)
{
    m_vehicles.append(vehicle);
    emit vehicleAdded(vehicle);
}

void VehicleService::removeVehicle(Vehicle* vehicle)
{
    m_vehicles.removeOne(vehicle);
    emit vehicleRemoved(vehicle);
}

void VehicleService::deleteVehicle(Vehicle* vehicle)
{
    this->removeVehicle(vehicle);
    vehicle->deleteLater();
}
