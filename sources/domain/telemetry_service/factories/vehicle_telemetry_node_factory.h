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
        VehicleTelemetryNodeFactory(const db::VehiclePtr& vehicle);

        TelemetryNode* create() override;

    private:
        db::VehiclePtr m_vehicle;
    };
}

#endif // VEHICLE_TELEMETRY_NODE_FACTORY_H
