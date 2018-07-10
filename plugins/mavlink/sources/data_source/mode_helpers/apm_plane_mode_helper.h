#ifndef APM_PLANE_MODE_HELPER_H
#define APM_PLANE_MODE_HELPER_H

#include "i_mode_helper.h"

namespace data_source
{
    class ApmPlaneModeHelper: public IModeHelper
    {
    public:
        ApmPlaneModeHelper();

        int modeToCustomMode(domain::Telemetry::VehicleMode mode) override;
        domain::Telemetry::VehicleMode customModeToMode(quint32 mode) override;

        virtual QList<domain::Telemetry::VehicleMode> availableModes() const override;
    };
}

#endif // APM_PLANE_MODE_HELPER_H
