#ifndef I_MODE_HELPER_H
#define I_MODE_HELPER_H

#include "vehicle_types.h"

namespace comm
{
    class IModeHelper
    {
    public:
        IModeHelper() {}
        virtual ~IModeHelper() {}

        virtual int modeToCustomMode(domain::vehicle::Mode mode) = 0;
        virtual domain::vehicle::Mode customModeToMode(quint32 mode) = 0;

        virtual QList<domain::vehicle::Mode> availableModes() const = 0;
    };
}

#endif // I_MODE_HELPER_H
