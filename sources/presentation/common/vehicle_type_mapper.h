#ifndef VEHICLE_TYPE_MAPPER_H
#define VEHICLE_TYPE_MAPPER_H

// Qt
#include <QUrl>

// Internal
#include "vehicle.h"

namespace presentation
{
    inline QUrl vehicleIcon(db::Vehicle::Type type)
    {
        switch (type) {
        case db::Vehicle::FixedWing:
            return QUrl("qrc:/indicators/fixed_wing_mark.svg");
        case db::Vehicle::FlyingWing:
            return QUrl("qrc:/indicators/flying_wing_mark.svg");
        case db::Vehicle::Quadcopter:
        case db::Vehicle::Tricopter:
        case db::Vehicle::Hexcopter:
        case db::Vehicle::Octocopter:
            return QUrl("qrc:/indicators/quadcopter_mark.svg");
        case db::Vehicle::Helicopter:
        case db::Vehicle::Coaxial:
            return QUrl("qrc:/indicators/helicopter_mark.svg");
        default:
            return QUrl("qrc:/indicators/unknown_mark.svg");
            break;
        }
    }
}

#endif // VEHICLE_TYPE_MAPPER_H
