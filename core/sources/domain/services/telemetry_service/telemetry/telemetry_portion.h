#ifndef TELEMETRY_PORTION_H
#define TELEMETRY_PORTION_H

// Internal
#include "telemetry.h"

namespace domain
{
    class TelemetryPortion: public QObject
    {
        Q_OBJECT

    public:
        explicit TelemetryPortion(Telemetry* node);
        ~TelemetryPortion() override;

    signals:
        void setParameter(const Telemetry::TelemetryList& path, const QVariant& value);

    private:
        Telemetry* m_node;
    };
}

#endif // TELEMETRY_PORTION_H
