#ifndef QML_DECLARATIONS_H
#define QML_DECLARATIONS_H

// Internal
#include "aerial_vehicle.h"

#include "link_description.h"
#include "mission_item.h"

void registerQmlTypes()
{
    qRegisterMetaType<domain::Attitude>("Attitude");
    qRegisterMetaType<domain::Position>("Position");
    qRegisterMetaType<domain::Gps>("Gps");
    qRegisterMetaType<domain::Wind>("Wind");
    qRegisterMetaType<domain::PowerSystem>("PowerSystem");

    qmlRegisterUncreatableType<db::LinkDescription>(
                "JAGCS", 1, 0, "LinkDescription", "Can't create entities in QML");
    qmlRegisterUncreatableType<db::MissionItem>(
                "JAGCS", 1, 0, "MissionItem", "Can't create entities in QML");
}

#endif // QML_DECLARATIONS_H
