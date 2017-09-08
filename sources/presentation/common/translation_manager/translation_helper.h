#ifndef TRANSLATION_HELPER_H
#define TRANSLATION_HELPER_H

// Qt
#include <QObject>

// Internal
#include "mission_item.h"
#include "vehicle.h"

namespace presentation
{
    class TranslationHelper : public QObject
    {
        Q_OBJECT

    public:
        explicit TranslationHelper(QObject *parent = nullptr);

        QString translateCommand(dao::MissionItem::Command command);
        QString translateVehicleType(dao::Vehicle::Type type);
    };
}

#endif // TRANSLATION_HELPER_H
