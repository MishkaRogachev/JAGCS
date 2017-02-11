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
    qRegisterMetaType<Wind>("Wind");
    qRegisterMetaType<PowerSystem>("PowerSystem");
}

AbstractVehicle* VehicleService::vehicle(int index) const
{
    return m_vehicles.at(index);
}

const QList<AbstractVehicle*>& VehicleService::vehicles() const
{
    return m_vehicles;
}

Vehicle* VehicleService::vehicleForId(uint8_t id)
{
    for (domain::AbstractVehicle* vehicle: m_vehicles)
    {
        if (vehicle->vehicleId() == id) return qobject_cast<Vehicle*>(vehicle);
    }
    return nullptr;
}

void VehicleService::addVehicle(AbstractVehicle* vehicle)
{
    m_vehicles.append(vehicle);
    emit vehicleAdded(vehicle);
}

void VehicleService::createVehicle(uint8_t vehicleId, int type)
{
    switch (type)
    {
    case Vehicle::FixedWingAircraft:
        this->addVehicle(new Vehicle(vehicleId, Vehicle::FixedWingAircraft, this));
        break;
    default:
        break;
    }
}

void VehicleService::removeVehicle(AbstractVehicle* vehicle)
{
    m_vehicles.removeOne(vehicle);
    emit vehicleRemoved(vehicle);
}

void VehicleService::deleteVehicle(AbstractVehicle* vehicle)
{
    this->removeVehicle(vehicle);
    vehicle->deleteLater();
}
