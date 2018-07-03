#ifndef PX4_MODE_HELPER_H
#define PX4_MODE_HELPER_H

#include "i_mode_helper.h"

namespace comm
{
    class Px4ModeHelper: public IModeHelper // TODO: separate copter and plane modes
    {
    public:
        Px4ModeHelper();

        int modeToCustomMode(domain::vehicle::Mode mode) override;
        domain::vehicle::Mode customModeToMode(quint32 mode) override;

        virtual QList<domain::vehicle::Mode> availableModes() const override;
    };
}

#endif // PX4_MODE_HELPER_H
