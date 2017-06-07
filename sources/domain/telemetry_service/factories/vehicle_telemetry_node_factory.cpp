#include "vehicle_telemetry_node_factory.h"

// Qt
#include <QCoreApplication>

// Internal
#include "vehicle.h"

#include "telemetry_node.h"
#include "telemetry_traits.h"

using namespace domain;

VehicleTelemetryNodeFactory::VehicleTelemetryNodeFactory(const db::VehiclePtr& vehicle):
    ITelemetryNodeFactory(),
    m_vehicle(vehicle)
{}

TelemetryNode* VehicleTelemetryNodeFactory::create()
{
    TelemetryNode* root = new TelemetryNode(qApp->translate("TelemetryNode",
                                            ("MAV %1")).arg(m_vehicle->mavId()));

    new TelemetryNode(telemetry::home, root);
    new TelemetryNode(telemetry::ahrs, root);
    new TelemetryNode(telemetry::satellite, root);
    new TelemetryNode(telemetry::barometric, root);
    new TelemetryNode(telemetry::navigator, root);
    new TelemetryNode(telemetry::powerSystem, root);

    return root;
}
