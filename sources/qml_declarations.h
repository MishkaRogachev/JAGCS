#ifndef QML_DECLARATIONS_H
#define QML_DECLARATIONS_H

#include "link_description.h"

void registerQmlTypes()
{
    qmlRegisterType<data_source::LinkDescription>("JAGCS", 1, 0, "LinkDescription");
}

#endif // QML_DECLARATIONS_H
