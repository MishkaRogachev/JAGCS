#include "vehicle_telemetry_factory.h"

// Qt
#include <QCoreApplication>

// Internal
#include "telemetry.h"

using namespace domain;

VehicleTelemetryFactory::VehicleTelemetryFactory():
    ITelemetryFactory()
{}

Telemetry* VehicleTelemetryFactory::create()
{
    Telemetry* root = new Telemetry(Telemetry::Root);

    new Telemetry(Telemetry::HomePosition, root);
    new Telemetry(Telemetry::Ahrs, root);
    new Telemetry(Telemetry::Satellite, root);
    new Telemetry(Telemetry::Barometric, root);
    new Telemetry(Telemetry::Navigator, root);
    new Telemetry(Telemetry::PowerSystem, root);

    return root;
}
