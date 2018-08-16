#include "apm_plane_mode_helper.h"

// Qt
#include <QMap>

using namespace data_source;

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

    QMap<quint32, Telemetry::VehicleMode> modeMap =
    {
        { MANUAL,       Telemetry::ManualMode },
        { CIRCLE,       Telemetry::CircleMode },
        { STABILIZE,    Telemetry::StabilizeMode },
        { ACRO,         Telemetry::AcroMode },
        { FBWA,         Telemetry::FbwaMode },
        { FBWB,         Telemetry::FbwbMode },
        { CRUISE,       Telemetry::CruiseMode },
        { AUTOTUNE,     Telemetry::AutotuneMode },
        { AUTO,         Telemetry::MissionMode },
        { RTL,          Telemetry::ReturnMode },
        { LOITER,       Telemetry::LoiterMode },
        { AVOID,        Telemetry::AvoidMode },
        { GUIDED,       Telemetry::NavToMode },
        { INITIALIZING, Telemetry::InitMode }
    };

    const QList<Telemetry::VehicleMode> availableModes
    {
        //        Telemetry::VehicleMode::ManualMode,
        //        Telemetry::VehicleMode::StabilizeMode,
        //        Telemetry::VehicleMode::AcroMode,
        //        Telemetry::VehicleMode::AutotuneMode,
        //        Telemetry::VehicleMode::CruiseMode,
        Telemetry::VehicleMode::ReturnMode,
        Telemetry::VehicleMode::MissionMode,
        Telemetry::VehicleMode::CircleMode,
        Telemetry::VehicleMode::LoiterMode,
        Telemetry::VehicleMode::NavToMode,
        Telemetry::VehicleMode::FbwaMode,
        Telemetry::VehicleMode::FbwbMode
    };
}

ApmPlaneModeHelper::ApmPlaneModeHelper():
    IModeHelper()
{}

int ApmPlaneModeHelper::modeToCustomMode(Telemetry::VehicleMode mode)
{
    return ::modeMap.key(mode, -1);
}

Telemetry::VehicleMode ApmPlaneModeHelper::customModeToMode(quint32 mode)
{
    return ::modeMap.value(mode, Telemetry::NoneMode);
}

QList<Telemetry::VehicleMode> ApmPlaneModeHelper::availableModes() const
{
    return ::availableModes;
}
