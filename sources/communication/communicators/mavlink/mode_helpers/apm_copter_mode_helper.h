#ifndef APM_COPTER_MODE_HELPER_H
#define APM_COPTER_MODE_HELPER_H

#include "i_mode_helper.h"

namespace comm
{
    class ApmCopterModeHelper: public IModeHelper
    {
    public:
        ApmCopterModeHelper();

        quint32 modeToCustomMode(domain::Mode mode) override;
        domain::Mode customModeToMode(quint32 mode) override;

        virtual QList<domain::Mode> availableModes() const override;
    };
}

#endif // APM_COPTER_MODE_HELPER_H
