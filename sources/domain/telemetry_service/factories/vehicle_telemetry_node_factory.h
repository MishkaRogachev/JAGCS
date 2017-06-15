#ifndef VEHICLE_TELEMETRY_NODE_FACTORY_H
#define VEHICLE_TELEMETRY_NODE_FACTORY_H

// Internal
#include "i_telemetry_node_factory.h"
#include "db_traits.h"

namespace domain
{
    class VehicleTelemetryNodeFactory: public ITelemetryNodeFactory
    {
    public:
        VehicleTelemetryNodeFactory();

        TelemetryNode* create() override;
    };
}

#endif // VEHICLE_TELEMETRY_NODE_FACTORY_H
