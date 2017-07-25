#ifndef VEHICLE_TYPE_MAPPER_H
#define VEHICLE_TYPE_MAPPER_H

// Qt
#include <QUrl>

// Internal
#include "vehicle.h"

namespace presentation
{
    inline QUrl vehicleIcon(dao::Vehicle::Type type)
    {
        switch (type) {
        case dao::Vehicle::FixedWing:
            return QUrl("qrc:/indicators/fixed_wing_mark.svg");
        case dao::Vehicle::FlyingWing:
            return QUrl("qrc:/indicators/flying_wing_mark.svg");
        case dao::Vehicle::Quadcopter:
        case dao::Vehicle::Tricopter:
        case dao::Vehicle::Hexcopter:
        case dao::Vehicle::Octocopter:
            return QUrl("qrc:/indicators/quadcopter_mark.svg");
        case dao::Vehicle::Helicopter:
        case dao::Vehicle::Coaxial:
            return QUrl("qrc:/indicators/helicopter_mark.svg");
        default:
            return QUrl("qrc:/indicators/unknown_mark.svg");
            break;
        }
    }
}

#endif // VEHICLE_TYPE_MAPPER_H
