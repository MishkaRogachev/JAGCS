#ifndef APM_COPTER_MODE_HELPER_H
#define APM_COPTER_MODE_HELPER_H

#include "i_mode_helper.h"

namespace comm
{
    class ApmCopterModeHelper: public IModeHelper
    {
    public:
        ApmCopterModeHelper();

        int modeToCustomMode(domain::vehicle::Mode mode) override;
        domain::vehicle::Mode customModeToMode(quint32 mode) override;

        virtual QList<domain::vehicle::Mode> availableModes() const override;
    };
}

#endif // APM_COPTER_MODE_HELPER_H
