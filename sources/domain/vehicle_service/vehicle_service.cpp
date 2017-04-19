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
    QMap<VehicleDescriptionPtr, BaseVehicle*> vehicles;

    BaseVehicle* vehicleFromDescription(const VehicleDescriptionPtr& description)
    {
        DescriptionVehicleFactory factory(description);

        vehicles[description] = factory.create();
        return vehicles[description];
    }
};

VehicleService::VehicleService(DbEntry* entry, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->entry = entry;

    for (const VehicleDescriptionPtr& description: d->entry->loadVehicles())
    {
        BaseVehicle* vehicle = d->vehicleFromDescription(description);
        vehicle->setParent(this);
    }
}

VehicleService::~VehicleService()
{}

VehicleDescriptionPtrList VehicleService::vehicles() const
{
    return d->vehicles.keys();
}
