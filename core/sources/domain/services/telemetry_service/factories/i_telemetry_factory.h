#ifndef I_TELEMETRY_FACTORY_H
#define I_TELEMETRY_FACTORY_H

namespace domain
{
    class Telemetry;

    class ITelemetryFactory
    {
    public:
        ITelemetryFactory() {}
        virtual ~ITelemetryFactory() {}

        virtual Telemetry* create() = 0;
    };
}

#endif // I_TELEMETRY_FACTORY_H
