#include "apm_copter_mode_helper.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QMap>

namespace
{
    enum ApmCopterMode: quint32
    {
        STABILIZE       = 0,
        ACRO            = 1,
        ALT_HOLD        = 2,
        AUTO            = 3,
        GUIDED          = 4,
        LOITER          = 5,
        RTL             = 6,
        CIRCLE          = 7,
        POSITION        = 8,
        LAND            = 9,
        OF_LOITER       = 10,
        DRIFT           = 11,
        RESERVED_12     = 12,
        SPORT           = 13,
        FLIP            = 14,
        AUTOTUNE        = 15,
        POS_HOLD        = 16,
        BRAKE           = 17,
        THROW           = 18,
        AVOID_ADSB      = 19,
        GUIDED_NOGPS    = 20,
        SAFE_RTL        = 21
    };

    QMap<quint32, domain::vehicle::Mode> modeMap =
    {
        { STABILIZE,    domain::vehicle::Mode::Stabilize },
        { ACRO,         domain::vehicle::Mode::Acro },
        { ALT_HOLD,     domain::vehicle::Mode::AltHold },
        { AUTO,         domain::vehicle::Mode::Mission },
        { GUIDED,       domain::vehicle::Mode::NavTo },
        { LOITER,       domain::vehicle::Mode::Loiter },
        { RTL,          domain::vehicle::Mode::Return },
        { CIRCLE,       domain::vehicle::Mode::Circle },
        { LAND,         domain::vehicle::Mode::Landing },
        { AUTOTUNE,     domain::vehicle::Mode::Autotune },
        { POS_HOLD,     domain::vehicle::Mode::HoldPosition },
        { THROW,        domain::vehicle::Mode::Throw },
        { AVOID_ADSB,   domain::vehicle::Mode::Avoid }
    };

    const QList<domain::vehicle::Mode> availableModes
    {
        domain::vehicle::Mode::Return,
        domain::vehicle::Mode::Mission,
        domain::vehicle::Mode::Loiter,
        domain::vehicle::Mode::AltHold,
        domain::vehicle::Mode::Stabilize
    };
}

using namespace comm;

ApmCopterModeHelper::ApmCopterModeHelper():
    IModeHelper()
{}

int ApmCopterModeHelper::modeToCustomMode(domain::vehicle::Mode mode)
{
    return ::modeMap.key(mode, -1);
}

domain::vehicle::Mode ApmCopterModeHelper::customModeToMode(quint32 mode)
{
    return ::modeMap.value(mode, domain::vehicle::Mode::None);
}

QList<domain::vehicle::Mode> ApmCopterModeHelper::availableModes() const
{
     return ::availableModes;
}
