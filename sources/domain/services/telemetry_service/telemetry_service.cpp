#include "telemetry_service.h"

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "vehicle_service.h"
#include "vehicle.h"

#include "telemetry.h"
#include "telemetry_portion.h"
#include "vehicle_telemetry_factory.h"

#include "vehicle_types.h"

using namespace domain;

class TelemetryService::Impl
{
public:
    domain::VehicleService* service;

    QMap<int, Telemetry*> vehicleNodes;
    Telemetry radioNode;
    Telemetry swarmNode;

    Impl():
        radioNode(Telemetry::Root),
        swarmNode(Telemetry::Root)
    {}
};

TelemetryService::TelemetryService(VehicleService* service, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    qRegisterMetaType<Telemetry::TelemetryList>("Telemetry::TelemetryList");
    qRegisterMetaType<Telemetry::TelemetryMap>("Telemetry::TelemetryMap");

    d->service = service;
    connect(d->service, &VehicleService::vehicleAdded, this, &TelemetryService::onVehicleAdded);
    connect(d->service, &VehicleService::vehicleRemoved, this, &TelemetryService::onVehicleRemoved);

    VehicleTelemetryFactory factory;
    for (const dto::VehiclePtr& vehicle: d->service->vehicles())
    {
        d->vehicleNodes[vehicle->id()] = factory.create();
    }
}

TelemetryService::~TelemetryService()
{}

QList<Telemetry*> TelemetryService::rootNodes() const
{
    QList<Telemetry*> list;

    list.append(d->vehicleNodes.values());
    list.append(&d->radioNode);

    return list;
}

Telemetry* TelemetryService::vehicleNode(int vehicleId) const
{
    return d->vehicleNodes.value(vehicleId, nullptr);
}

Telemetry* TelemetryService::mavNode(int mavId) const
{
    return this->vehicleNode(d->service->vehicleIdByMavId(mavId));
}

Telemetry* TelemetryService::radioNode() const
{
    return &d->radioNode;
}

Telemetry* TelemetryService::swarmNode() const
{
    return &d->swarmNode;
}

void TelemetryService::onVehicleAdded(const dto::VehiclePtr& vehicle)
{
    if (d->vehicleNodes.contains(vehicle->id())) return;

    VehicleTelemetryFactory factory;
    d->vehicleNodes[vehicle->id()] = factory.create();
}

void TelemetryService::onVehicleRemoved(const dto::VehiclePtr& vehicle)
{
    if (!d->vehicleNodes.contains(vehicle->id())) return;

    // FIXME: crash on removing nodes
    //delete d->vehicleNodes[vehicle->id()];
}


