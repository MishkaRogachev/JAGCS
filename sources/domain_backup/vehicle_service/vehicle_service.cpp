#include "vehicle_service.h"

// Qt
#include <QMap>
#include <QTimerEvent>
#include <QDebug>

// Internal
#include "aerial_vehicle.h"

namespace
{
    const int forgotVehicleTimeout = 5000;
}

using namespace domain;

class VehicleService::Impl
{
public:
    QMap<uint8_t, AbstractVehicle*> vehicles;
    QMap<int, AbstractVehicle*> vehicleTimers;
};

VehicleService::VehicleService(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    qRegisterMetaType<Attitude>("Attitude");
    qRegisterMetaType<Position>("Position");
    qRegisterMetaType<Gps>("Gps");
    qRegisterMetaType<Wind>("Wind");
    qRegisterMetaType<PowerSystem>("PowerSystem");
}

VehicleService::~VehicleService()
{
    delete d;
}

QList<AbstractVehicle*> VehicleService::vehicles() const
{
    return d->vehicles.values();
}

AbstractVehicle* VehicleService::vehicle(uint8_t id) const
{
    return d->vehicles.value(id, nullptr);
}

BaseVehicle* VehicleService::baseVehicle(uint8_t id) const
{
    return qobject_cast<BaseVehicle*>(this->vehicle(id));
}

AerialVehicle* VehicleService::aerialVehicle(uint8_t id) const
{
    return qobject_cast<AerialVehicle*>(this->vehicle(id));
}

void VehicleService::addVehicle(AbstractVehicle* vehicle)
{
    d->vehicles[vehicle->vehicleId()] = vehicle;
    d->vehicleTimers[this->startTimer(::forgotVehicleTimeout)] = vehicle;
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
    d->vehicles.remove(vehicle->vehicleId());
    this->killTimer(d->vehicleTimers.key(vehicle));
    d->vehicleTimers.remove(d->vehicleTimers.key(vehicle));

    emit vehicleRemoved(vehicle);
}

void VehicleService::deleteVehicle(AbstractVehicle* vehicle)
{
    this->removeVehicle(vehicle);
    vehicle->deleteLater();
}

void VehicleService::prolongVehicle(AbstractVehicle* vehicle)
{
    this->killTimer(d->vehicleTimers.key(vehicle));
    d->vehicleTimers[this->startTimer(::forgotVehicleTimeout)] = vehicle;
}

void VehicleService::timerEvent(QTimerEvent* event)
{
    if (d->vehicleTimers.contains(event->timerId()))
    {
        this->removeVehicle(d->vehicleTimers.value(event->timerId()));
    }
    QObject::timerEvent(event);
}
