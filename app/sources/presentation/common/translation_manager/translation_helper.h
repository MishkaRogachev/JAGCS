#ifndef TRANSLATION_HELPER_H
#define TRANSLATION_HELPER_H

// Qt
#include <QObject>
#include <QUrl>

// Internal
#include "mission_item.h"
#include "vehicle.h"
#include "telemetry.h"

namespace presentation
{
    class TranslationHelper : public QObject
    {
        Q_OBJECT

    public:
        explicit TranslationHelper(QObject* parent = nullptr);

        Q_INVOKABLE QString translateCommand(dto::MissionItem::Command command);
        Q_INVOKABLE QString translateVehicleType(dto::Vehicle::Type type);
        Q_INVOKABLE QUrl imageFromVehicleType(dto::Vehicle::Type type);

        Q_INVOKABLE QString translateVehicleMode(domain::Telemetry::VehicleMode mode);
        Q_INVOKABLE QString translateVehicleState(domain::Telemetry::SystemState state);
        Q_INVOKABLE QUrl imageFromVehicleState(domain::Telemetry::SystemState state);
    };
}

#endif // TRANSLATION_HELPER_H
