#include "vehicle_service.h"

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "db_entry.h"
#include "vehicle_description.h"

#include "aerial_vehicle.h"
#include "description_vehicle_factory.h"

using namespace db;
using namespace domain;

class VehicleService::Impl
{
public:
    DbEntry* entry;

    QList<VehicleDescriptionPtr> descriptions;
    QMap<VehicleDescriptionPtr, BaseVehicle*> descriptedVehicles;

    BaseVehicle* vehicleFromDescription(const VehicleDescriptionPtr& description)
    {
        DescriptionVehicleFactory factory(description);

        descriptedVehicles[description] = factory.create();
        return descriptedVehicles[description];
    }
};

VehicleService::VehicleService(DbEntry* entry, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->entry = entry;

    for (const VehicleDescriptionPtr& description: d->entry->loadVehicles())
    {
        d->descriptions.append(description);
        BaseVehicle* vehicle = d->vehicleFromDescription(description);
        vehicle->setParent(this);
    }
}

VehicleService::~VehicleService()
{
    for (const VehicleDescriptionPtr& description: d->descriptions)
    {
        d->entry->save(description);
    }
}

VehicleDescriptionPtrList VehicleService::descriptions() const
{
    return d->descriptions;
}

VehicleDescriptionPtr VehicleService::findDescriptiontByMavId(quint8 mavId) const
{
    auto it = std::find_if(d->descriptions.cbegin(), d->descriptions.cend(),
                           [mavId](const VehicleDescriptionPtr& description)
    {
        return description->mavId() == mavId;
    });

    if (it != d->descriptions.cend()) return *it;
    return VehicleDescriptionPtr();
}

BaseVehicle* VehicleService::baseVehicle(const VehicleDescriptionPtr& description)
{
    return d->descriptedVehicles.value(description, nullptr);
}

BaseVehicle* VehicleService::baseVehicle(quint8 mavId)
{
    return this->baseVehicle(this->findDescriptiontByMavId(mavId));
}

AerialVehicle* VehicleService::aerialVehicle(const VehicleDescriptionPtr& description)
{
    return qobject_cast<AerialVehicle*>(this->baseVehicle(description));
}

AerialVehicle* VehicleService::aerialVehicle(quint8 mavId)
{
    return this->aerialVehicle(this->findDescriptiontByMavId(mavId));
}

void VehicleService::saveDescription(const VehicleDescriptionPtr& description)
{
    BaseVehicle* vehicle;

    if (d->descriptions.contains(description))
    {
        vehicle = d->descriptedVehicles[description];
        vehicle->setMavId(description->mavId());
    }
    else
    {
        d->descriptions.append(description);
        vehicle = d->vehicleFromDescription(description);
        vehicle->setParent(this);
        emit vehicleAdded(description);
    }

    d->entry->save(description);
}

void VehicleService::removeByDescription(const VehicleDescriptionPtr& description)
{
    d->descriptions.removeOne(description);
    BaseVehicle* vehicle = d->descriptedVehicles.take(description);
    delete vehicle;

    d->entry->remove(description);

    emit vehicleRemoved(description);
}
