#ifndef I_MODE_HELPER_H
#define I_MODE_HELPER_H

#include "telemetry.h"

namespace data_source
{
    class IModeHelper
    {
    public:
        IModeHelper() {}
        virtual ~IModeHelper() {}

        virtual int modeToCustomMode(domain::Telemetry::VehicleMode mode) = 0;
        virtual domain::Telemetry::VehicleMode customModeToMode(quint32 mode) = 0;

        virtual QList<domain::Telemetry::VehicleMode> availableModes() const = 0;
    };
}

#endif // I_MODE_HELPER_H
