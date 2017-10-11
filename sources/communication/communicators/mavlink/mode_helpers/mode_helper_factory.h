#ifndef MODE_HELPER_FACTORY_H
#define MODE_HELPER_FACTORY_H

#include "i_mode_helper.h"

namespace comm
{
    class ModeHelperFactory
    {
    public:
        IModeHelper* create(uint8_t autopilot, uint8_t type);
    };
}

#endif // MODE_HELPER_FACTORY_H
