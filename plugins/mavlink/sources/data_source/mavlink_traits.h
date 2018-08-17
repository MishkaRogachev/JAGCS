#ifndef MAVLINK_TRAITS_H
#define MAVLINK_TRAITS_H

#include <QStringList>

namespace data_source 
{
    namespace protocols
    {
#ifdef MAVLINK_V2
        const static QStringList mavlinkProtocols { "MAVLink1", "MAVLink2"};
#else
        const static QStringList mavlink { "MAVLink1" };
#endif
    }
}

#endif // MAVLINK_TRAITS_H
