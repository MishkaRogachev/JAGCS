#ifndef QML_DECLARATIONS_H
#define QML_DECLARATIONS_H

// Internal
#include "vehicle.h"
#include "link_description.h"
#include "mission_item.h"
#include "video_source.h"

void registerQmlTypes()
{
    qmlRegisterUncreatableType<dao::Vehicle>(
                "JAGCS", 1, 0, "Vehicle", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::LinkDescription>(
                "JAGCS", 1, 0, "LinkDescription", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::MissionItem>(
                "JAGCS", 1, 0, "MissionItem", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::VideoSource>(
                "JAGCS", 1, 0, "VideoSource", "Can't create entities in QML");
}

#endif // QML_DECLARATIONS_H
