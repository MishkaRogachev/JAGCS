#ifndef QML_DECLARATIONS_H
#define QML_DECLARATIONS_H

// Internal
#include "link_description.h"
#include "mission_item.h"
#include "video_source.h"

void registerQmlTypes()
{
    qmlRegisterUncreatableType<db::LinkDescription>(
                "JAGCS", 1, 0, "LinkDescription", "Can't create entities in QML");
    qmlRegisterUncreatableType<db::MissionItem>(
                "JAGCS", 1, 0, "MissionItem", "Can't create entities in QML");
    qmlRegisterUncreatableType<db::VideoSource>(
                "JAGCS", 1, 0, "VideoSource", "Can't create entities in QML");
}

#endif // QML_DECLARATIONS_H
