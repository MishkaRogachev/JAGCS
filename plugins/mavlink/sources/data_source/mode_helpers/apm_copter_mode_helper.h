#ifndef APM_COPTER_MODE_HELPER_H
#define APM_COPTER_MODE_HELPER_H

#include "i_mode_helper.h"

namespace data_source
{
    class ApmCopterModeHelper: public IModeHelper
    {
    public:
        ApmCopterModeHelper();

        int modeToCustomMode(domain::Telemetry::VehicleMode mode) override;
        domain::Telemetry::VehicleMode customModeToMode(quint32 mode) override;

        virtual QList<domain::Telemetry::VehicleMode> availableModes() const override;
    };
}

#endif // APM_COPTER_MODE_HELPER_H
