#ifndef PX4_MODE_HELPER_H
#define PX4_MODE_HELPER_H

#include "i_mode_helper.h"

namespace data_source
{
    class Px4ModeHelper: public IModeHelper // TODO: separate copter and plane modes
    {
    public:
        Px4ModeHelper();

        int modeToCustomMode(domain::Telemetry::VehicleMode mode) override;
        domain::Telemetry::VehicleMode customModeToMode(quint32 mode) override;

        virtual QList<domain::Telemetry::VehicleMode> availableModes() const override;
    };
}

#endif // PX4_MODE_HELPER_H
