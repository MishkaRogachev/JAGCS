#ifndef APM_PLANE_MODE_HELPER_H
#define APM_PLANE_MODE_HELPER_H

#include "i_mode_helper.h"

namespace comm
{
    class ApmPlaneModeHelper: public IModeHelper
    {
    public:
        ApmPlaneModeHelper();

        int modeToCustomMode(domain::vehicle::Mode mode) override;
        domain::vehicle::Mode customModeToMode(quint32 mode) override;

        virtual QList<domain::vehicle::Mode> availableModes() const override;
    };
}

#endif // APM_PLANE_MODE_HELPER_H
