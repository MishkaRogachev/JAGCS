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

    QMap<quint32, domain::Telemetry::VehicleMode> modeMap =
    {
        { MANUAL,       domain::Telemetry::ManualMode },
        { CIRCLE,       domain::Telemetry::CircleMode },
        { STABILIZE,    domain::Telemetry::StabilizeMode },
        { ACRO,         domain::Telemetry::AcroMode },
        { FBWA,         domain::Telemetry::FbwaMode },
        { FBWB,         domain::Telemetry::FbwbMode },
        { CRUISE,       domain::Telemetry::CruiseMode },
        { AUTOTUNE,     domain::Telemetry::AutotuneMode },
        { AUTO,         domain::Telemetry::MissionMode },
        { RTL,          domain::Telemetry::ReturnMode },
        { LOITER,       domain::Telemetry::LoiterMode },
        { AVOID,        domain::Telemetry::AvoidMode },
        { GUIDED,       domain::Telemetry::NavToMode },
        { INITIALIZING, domain::Telemetry::InitMode }
    };

    const QList<domain::Telemetry::VehicleMode> availableModes
    {
        //        domain::Telemetry::VehicleMode::ManualMode,
        //        domain::Telemetry::VehicleMode::StabilizeMode,
        //        domain::Telemetry::VehicleMode::AcroMode,
        //        domain::Telemetry::VehicleMode::AutotuneMode,
        //        domain::Telemetry::VehicleMode::CruiseMode,
        domain::Telemetry::VehicleMode::ReturnMode,
        domain::Telemetry::VehicleMode::MissionMode,
        domain::Telemetry::VehicleMode::CircleMode,
        domain::Telemetry::VehicleMode::LoiterMode,
        domain::Telemetry::VehicleMode::NavToMode,
        domain::Telemetry::VehicleMode::FbwaMode,
        domain::Telemetry::VehicleMode::FbwbMode
    };
}

using namespace data_source;

ApmPlaneModeHelper::ApmPlaneModeHelper():
    IModeHelper()
{}

int ApmPlaneModeHelper::modeToCustomMode(domain::Telemetry::VehicleMode mode)
{
    return ::modeMap.key(mode, -1);
}

domain::Telemetry::VehicleMode ApmPlaneModeHelper::customModeToMode(quint32 mode)
{
    return ::modeMap.value(mode, domain::Telemetry::NoneMode);
}

QList<domain::Telemetry::VehicleMode> ApmPlaneModeHelper::availableModes() const
{
    return ::availableModes;
}
