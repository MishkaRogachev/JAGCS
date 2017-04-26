#ifndef QML_DECLARATIONS_H
#define QML_DECLARATIONS_H

#include "link_description.h"
#include "aerial_vehicle.h"

void registerQmlTypes()
{
    qRegisterMetaType<domain::Attitude>("Attitude");
    qRegisterMetaType<domain::Position>("Position");
    qRegisterMetaType<domain::Gps>("Gps");
    qRegisterMetaType<domain::Wind>("Wind");
    qRegisterMetaType<domain::PowerSystem>("PowerSystem");

    qmlRegisterUncreatableType<db::LinkDescription>("JAGCS", 1, 0, "LinkDescription",
                                                    "Can't create DB entities in QML");
}

#endif // QML_DECLARATIONS_H
