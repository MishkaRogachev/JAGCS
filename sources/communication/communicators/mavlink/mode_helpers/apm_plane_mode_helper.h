#ifndef APM_PLANE_MODE_HELPER_H
#define APM_PLANE_MODE_HELPER_H

#include "i_mode_helper.h"

namespace comm
{
    class ApmPlaneModeHelper: public IModeHelper
    {
    public:
        ApmPlaneModeHelper();

        int modeToCustomMode(domain::Mode mode) override;
        domain::Mode customModeToMode(quint32 mode) override;

        virtual QList<domain::Mode> availableModes() const override;
    };
}

#endif // APM_PLANE_MODE_HELPER_H
