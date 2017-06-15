#include "vehicle_telemetry_node_factory.h"

// Qt
#include <QCoreApplication>

// Internal
#include "telemetry_node.h"
#include "telemetry_traits.h"

using namespace domain;

VehicleTelemetryNodeFactory::VehicleTelemetryNodeFactory():
    ITelemetryNodeFactory()
{}

TelemetryNode* VehicleTelemetryNodeFactory::create()
{
    TelemetryNode* root = new TelemetryNode(TelemetryId::Root);

    new TelemetryNode(TelemetryId::Home, root);
    new TelemetryNode(TelemetryId::Ahrs, root);
    new TelemetryNode(TelemetryId::Satellite, root);
    new TelemetryNode(TelemetryId::Barometric, root);
    new TelemetryNode(TelemetryId::Navigator, root);
    new TelemetryNode(TelemetryId::PowerSystem, root);

    return root;
}
