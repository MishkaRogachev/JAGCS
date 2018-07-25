#include "apm_copter_mode_helper.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QMap>

using namespace data_source;

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

    QMap<quint32, Telemetry::VehicleMode> modeMap =
    {
        { STABILIZE,    Telemetry::StabilizeMode },
        { ACRO,         Telemetry::AcroMode },
        { ALT_HOLD,     Telemetry::AltHoldMode },
        { AUTO,         Telemetry::MissionMode },
        { GUIDED,       Telemetry::NavToMode },
        { LOITER,       Telemetry::LoiterMode },
        { RTL,          Telemetry::ReturnMode },
        { CIRCLE,       Telemetry::CircleMode },
        { LAND,         Telemetry::LandingMode },
        { AUTOTUNE,     Telemetry::AutotuneMode },
        { POS_HOLD,     Telemetry::HoldPositionMode },
        { THROW,        Telemetry::ThrowMode },
        { AVOID_ADSB,   Telemetry::AvoidMode }
    };

    const QList<Telemetry::VehicleMode> availableModes
    {
        Telemetry::ReturnMode,
        Telemetry::MissionMode,
        Telemetry::LoiterMode,
        Telemetry::AltHoldMode,
        Telemetry::StabilizeMode
    };
}

ApmCopterModeHelper::ApmCopterModeHelper():
    IModeHelper()
{}

int ApmCopterModeHelper::modeToCustomMode(Telemetry::VehicleMode mode)
{
    return ::modeMap.key(mode, -1);
}

Telemetry::VehicleMode ApmCopterModeHelper::customModeToMode(quint32 mode)
{
    return ::modeMap.value(mode, Telemetry::NoneMode);
}

QList<Telemetry::VehicleMode> ApmCopterModeHelper::availableModes() const
{
     return ::availableModes;
}
