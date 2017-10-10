#ifndef MODES_H
#define MODES_H

#include <QObject>

namespace domain
{
    Q_NAMESPACE
    Q_CLASSINFO("namespace", "domain")

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

    Q_ENUM_NS(Mode)
}

#endif // MODES_H
