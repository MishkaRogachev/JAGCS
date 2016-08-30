#ifndef MAVLINK_TRAITS_H
#define MAVLINK_TRAITS_H

// MAVLink
#include <mavlink_types.h>

namespace data_source
{
    namespace mavlink
    {
        inline void init()
        {
            qRegisterMetaType<mavlink_message_t>("mavlink_message_t");
        }
    }
}

#endif // MAVLINK_TRAITS_H
