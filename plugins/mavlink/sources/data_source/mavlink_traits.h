#ifndef MAVLINK_TRAITS_H
#define MAVLINK_TRAITS_H

#include <QStringList>

namespace data_source 
{
    namespace protocols
    {
#ifdef MAVLINK_V2
        const static QStringList mavlinkProtocols { "MAVLINK1", "MAVLINK2"};
#else
        const static QStringList mavlink { "MAVLINK1" };
#endif
    }
}

#endif // MAVLINK_TRAITS_H
