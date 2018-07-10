#ifndef MAVLINK_SETTINGS_H
#define MAVLINK_SETTINGS_H

#include <QString>

namespace settings
{
    namespace communication
    {
        const QString systemId = "Communication/systemId";
        const QString componentId = "Communication/componentId";
        const QString heartbeat = "Communication/heartbeat";
        const QString timeout = "Communication/timeout";
    }
}

#endif // MAVLINK_SETTINGS_H
