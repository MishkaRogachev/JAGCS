#include "telemetry_service.h"

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "db_facade.h"
#include "vehicle.h"

#include "telemetry_node.h"
#include "vehicle_telemetry_node_factory.h"

using namespace domain;

class TelemetryService::Impl
{
public:
    db::DbFacade* facade;

    QMap<int, TelemetryNode*> vehicleNodes;
};

TelemetryService::TelemetryService(db::DbFacade* facade, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->facade = facade;
    connect(d->facade, &db::DbFacade::vehicleRemoved, this, &TelemetryService::onVehicleRemoved);
}

TelemetryService::~TelemetryService()
{}

QList<TelemetryNode*> TelemetryService::rootNodes() const
{
    return d->vehicleNodes.values();
}

TelemetryNode* TelemetryService::node(int vehicleId) const
{
    if (!d->vehicleNodes.contains(vehicleId))
    {
        VehicleTelemetryNodeFactory factory(d->facade->vehicle(vehicleId));
        d->vehicleNodes[vehicleId] = factory.create();
    }
    return d->vehicleNodes.value(vehicleId, nullptr);
}

TelemetryNode* TelemetryService::nodeByMavId(int mavId) const
{
    return this->node(d->facade->vehicleIdByMavId(mavId));
}

void TelemetryService::onVehicleRemoved(const db::VehiclePtr& vehicle)
{
    delete d->vehicleNodes.take(vehicle->id());
}


