#ifndef APM_COPTER_MODE_HELPER_H
#define APM_COPTER_MODE_HELPER_H

#include "i_mode_helper.h"

namespace data_source
{
    class ApmCopterModeHelper: public IModeHelper
    {
    public:
        ApmCopterModeHelper();

        int modeToCustomMode(Telemetry::VehicleMode mode) override;
        Telemetry::VehicleMode customModeToMode(quint32 mode) override;

        virtual QList<Telemetry::VehicleMode> availableModes() const override;
    };
}

#endif // APM_COPTER_MODE_HELPER_H
