#ifndef I_MODE_HELPER_H
#define I_MODE_HELPER_H

#include "modes.h"

namespace comm
{
    class IModeHelper
    {
    public:
        IModeHelper() {}
        virtual ~IModeHelper() {}

        virtual int modeToCustomMode(domain::Mode mode) = 0;
        virtual domain::Mode customModeToMode(quint32 mode) = 0;

        virtual QList<domain::Mode> availableModes() const = 0;
    };
}

#endif // I_MODE_HELPER_H
