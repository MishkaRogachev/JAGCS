#include "vehicle_service.h"

// Qt
#include <QDebug>

// Internal
#include "aerial_vehicle.h"

using namespace domain;

VehicleService::VehicleService(QObject* parent):
    QObject(parent)
{
    qRegisterMetaType<Attitude>("Attitude");
    qRegisterMetaType<Position>("Position");
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

AbstractVehicle* VehicleService::vehicleForId(uint8_t id) const
{
    for (domain::AbstractVehicle* vehicle: m_vehicles)
    {
        if (vehicle->vehicleId() == id) return vehicle;
    }
    return nullptr;
}

BaseVehicle* VehicleService::baseVehicle(uint8_t id) const
{
    return qobject_cast<BaseVehicle*>(this->vehicleForId(id));
}

AerialVehicle* VehicleService::aerialVehicle(uint8_t id) const
{
    return qobject_cast<AerialVehicle*>(this->vehicleForId(id));
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
    case AerialVehicle::FixedWingAircraft:
    case AerialVehicle::Multirotor:
    case AerialVehicle::Helicopter:
    case AerialVehicle::Airship:
    case AerialVehicle::Vtol:
        this->addVehicle(new AerialVehicle(vehicleId,
                                           AerialVehicle::Type(type),
                                           this));
        break;
    default:
        this->addVehicle(new BaseVehicle(vehicleId, type, this));
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
