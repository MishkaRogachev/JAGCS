#ifndef I_TELEMETRY_NODE_FACTORY_H
#define I_TELEMETRY_NODE_FACTORY_H

namespace domain
{
    class TelemetryNode;

    class ITelemetryNodeFactory
    {
    public:
        ITelemetryNodeFactory() {}
        virtual ~ITelemetryNodeFactory() {}

        virtual TelemetryNode* create() = 0;
    };
}

#endif // I_TELEMETRY_NODE_FACTORY_H
