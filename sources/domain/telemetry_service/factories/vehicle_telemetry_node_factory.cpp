#include "vehicle_telemetry_node_factory.h"

// Internal
#include "telemetry_node.h"
#include "telemetry_traits.h"

using namespace domain;

VehicleTelemetryNodeFactory::VehicleTelemetryNodeFactory(const db::VehiclePtr& vehicle):
    m_vehicle(vehicle)
{}

TelemetryNode* VehicleTelemetryNodeFactory::create()
{
    TelemetryNode* root = new TelemetryNode(tr("MAV %1").arg(vehicle->mavId()));

    new TelemetryNode(telemetry::navi, root);

    return root;
}
