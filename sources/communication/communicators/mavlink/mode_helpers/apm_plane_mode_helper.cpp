#include "apm_plane_mode_helper.h"

// Qt
#include <QMap>

namespace
{
    enum ApmPlaneMode: quint32
    {
        MANUAL          = 0,
        CIRCLE          = 1,
        STABILIZE       = 2,
        TRAINING        = 3,
        ACRO            = 4,
        FBWA            = 5,
        FBWB            = 6,
        CRUISE          = 7,
        AUTOTUNE        = 8,
        RESERVED_9      = 9,
        AUTO            = 10,
        RTL             = 11,
        LOITER          = 12,
        RESERVED_13     = 13,
        AVOID           = 14,
        GUIDED          = 15,
        INITIALIZING    = 16,
        QSTABILIZE      = 17,
        QHOVER          = 18,
        QLOITER         = 19,
        QLAND           = 20,
        QRTL            = 21
    };

    QMap<quint32, domain::vehicle::Mode> modeMap =
    {
        { MANUAL,       domain::vehicle::Mode::Manual },
        { CIRCLE,       domain::vehicle::Mode::Circle },
        { STABILIZE,    domain::vehicle::Mode::Stabilize },
        { ACRO,         domain::vehicle::Mode::Acro },
        { FBWA,         domain::vehicle::Mode::Fbwa },
        { FBWB,         domain::vehicle::Mode::Fbwb },
        { CRUISE,       domain::vehicle::Mode::Cruise },
        { AUTOTUNE,     domain::vehicle::Mode::Autotune },
        { AUTO,         domain::vehicle::Mode::Mission },
        { RTL,          domain::vehicle::Mode::Return },
        { LOITER,       domain::vehicle::Mode::Loiter },
        { AVOID,        domain::vehicle::Mode::Avoid },
        { GUIDED,       domain::vehicle::Mode::NavTo },
        { INITIALIZING, domain::vehicle::Mode::Init }
    };
}

using namespace comm;

ApmPlaneModeHelper::ApmPlaneModeHelper():
    IModeHelper()
{}

int ApmPlaneModeHelper::modeToCustomMode(domain::vehicle::Mode mode)
{
    return ::modeMap.key(mode, -1);
}

domain::vehicle::Mode ApmPlaneModeHelper::customModeToMode(quint32 mode)
{
    return ::modeMap.value(mode, domain::vehicle::Mode::None);
}

QList<domain::vehicle::Mode> ApmPlaneModeHelper::availableModes() const
{
    return {
//        domain::vehicle::Mode::Manual,
//        domain::vehicle::Mode::Stabilize,
//        domain::vehicle::Mode::Acro,
//        domain::vehicle::Mode::Autotune,
        domain::vehicle::Mode::Circle,
        domain::vehicle::Mode::Loiter,
        domain::vehicle::Mode::Fbwa,
        domain::vehicle::Mode::Fbwb,
        domain::vehicle::Mode::Cruise,
        domain::vehicle::Mode::Mission,
        domain::vehicle::Mode::NavTo,
        domain::vehicle::Mode::Return
    };
}
