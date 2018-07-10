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

    QMap<quint32, domain::Telemetry::VehicleMode> modeMap =
    {
        { STABILIZE,    domain::Telemetry::StabilizeMode },
        { ACRO,         domain::Telemetry::AcroMode },
        { ALT_HOLD,     domain::Telemetry::AltHoldMode },
        { AUTO,         domain::Telemetry::MissionMode },
        { GUIDED,       domain::Telemetry::NavToMode },
        { LOITER,       domain::Telemetry::LoiterMode },
        { RTL,          domain::Telemetry::ReturnMode },
        { CIRCLE,       domain::Telemetry::CircleMode },
        { LAND,         domain::Telemetry::LandingMode },
        { AUTOTUNE,     domain::Telemetry::AutotuneMode },
        { POS_HOLD,     domain::Telemetry::HoldPositionMode },
        { THROW,        domain::Telemetry::ThrowMode },
        { AVOID_ADSB,   domain::Telemetry::AvoidMode }
    };

    const QList<domain::Telemetry::VehicleMode> availableModes
    {
        domain::Telemetry::ReturnMode,
        domain::Telemetry::MissionMode,
        domain::Telemetry::LoiterMode,
        domain::Telemetry::AltHoldMode,
        domain::Telemetry::StabilizeMode
    };
}

using namespace data_source;

ApmCopterModeHelper::ApmCopterModeHelper():
    IModeHelper()
{}

int ApmCopterModeHelper::modeToCustomMode(domain::Telemetry::VehicleMode mode)
{
    return ::modeMap.key(mode, -1);
}

domain::Telemetry::VehicleMode ApmCopterModeHelper::customModeToMode(quint32 mode)
{
    return ::modeMap.value(mode, domain::Telemetry::NoneMode);
}

QList<domain::Telemetry::VehicleMode> ApmCopterModeHelper::availableModes() const
{
     return ::availableModes;
}
