#include "vehicle_service.h"

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "db_entry.h"
#include "vehicle_description.h"

#include "base_vehicle.h"
#include "description_vehicle_factory.h"

using namespace data_source;
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

VehicleDescriptionPtrList VehicleService::vehicles() const
{
    return d->descriptions;
}

void VehicleService::saveVehicle(const VehicleDescriptionPtr& description)
{
    BaseVehicle* vehicle;

    if (d->descriptions.contains(description))
    {
        vehicle = d->descriptedVehicles[description];
        // TODO: update vehicle
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

void VehicleService::removeVehicle(const VehicleDescriptionPtr& description)
{
    d->descriptions.removeOne(description);
    BaseVehicle* vehicle = d->descriptedVehicles.take(description);
    delete vehicle;

    d->entry->remove(description);

    emit vehicleRemoved(description);
}
