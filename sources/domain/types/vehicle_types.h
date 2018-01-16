#ifndef VEHICLE_TYPES_H
#define VEHICLE_TYPES_H

#include <QObject>

namespace domain
{
    namespace vehicle
    {
        Q_NAMESPACE
        Q_CLASSINFO("namespace", "domain::vehicle")

        enum class Mode {
            None,
            Init,
            Manual,
            Stabilize,
            Acro,
            CtrlByAttitude,
            CtrlByAltitude,
            HoldPosition,
            Cruise,
            Autotune,
            Guided,
            Loiter,
            Circle,
            Return,
            Takeoff,
            Landing,
            Mission,
            Throw,
            Avoid,
            Follow
        };

        enum class SystemState
        {
            UnknownState,
            Boot,
            Calibrating,
            Standby,
            Active,
            Critical,
            Emergency
        };

        Q_ENUM_NS(Mode)
        Q_ENUM_NS(SystemState)
    }
}

#endif // VEHICLE_TYPES_H
