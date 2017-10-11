#ifndef PX4_MODE_HELPER_H
#define PX4_MODE_HELPER_H

#include "i_mode_helper.h"

namespace comm
{
    class Px4ModeHelper: public IModeHelper // TODO: separate copter and plane modes
    {
    public:
        Px4ModeHelper();

        quint32 modeToCustomMode(domain::Mode mode) override;
        domain::Mode customModeToMode(quint32 mode) override;

        virtual QList<domain::Mode> availableModes() const override;
    };
}

#endif // PX4_MODE_HELPER_H
