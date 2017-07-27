#ifndef VEHICLE_TELEMETRY_FACTORY_H
#define VEHICLE_TELEMETRY_FACTORY_H

// Internal
#include "i_telemetry_factory.h"
#include "dao_traits.h"

namespace domain
{
    class VehicleTelemetryFactory: public ITelemetryFactory
    {
    public:
        VehicleTelemetryFactory();

        Telemetry* create() override;
    };
}

#endif // VEHICLE_TELEMETRY_FACTORY_H
