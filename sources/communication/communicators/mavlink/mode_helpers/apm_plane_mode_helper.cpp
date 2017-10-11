#include "apm_plane_mode_helper.h"

// Qt
#include <QMap>

namespace
{
    QMap<quint32, domain::Mode> modeMap =
    {
        { 0, domain::Mode::Manual },
        { 1, domain::Mode::Circle },
        { 2, domain::Mode::Stabilize },
        { 4, domain::Mode::Acro },
        { 5, domain::Mode::CtrlByAttitude },
        { 6, domain::Mode::CtrlByAltitude },
        { 7, domain::Mode::Cruise },
        { 8, domain::Mode::Autotune },
        { 10, domain::Mode::Mission },
        { 11, domain::Mode::Return },
        { 12, domain::Mode::Loiter },
        { 14, domain::Mode::Avoid },
        { 15, domain::Mode::Guided },
        { 16, domain::Mode::Init }
    };
}

using namespace comm;

ApmPlaneModeHelper::ApmPlaneModeHelper():
    IModeHelper()
{}

quint32 ApmPlaneModeHelper::modeToCustomMode(domain::Mode mode)
{
    return ::modeMap.key(mode, 0);
}

domain::Mode ApmPlaneModeHelper::customModeToMode(quint32 mode)
{
    return ::modeMap.value(mode, domain::Mode::None);
}

QList<domain::Mode> ApmPlaneModeHelper::availableModes() const
{
    return {
        domain::Mode::Manual,
        domain::Mode::Stabilize,
        domain::Mode::CtrlByAttitude,
        domain::Mode::CtrlByAltitude,
        domain::Mode::Autotune,
        domain::Mode::Acro,
        domain::Mode::Cruise,
        domain::Mode::Mission,
        domain::Mode::Return,
        domain::Mode::Loiter,
        domain::Mode::Circle,
        domain::Mode::Guided
    };
}
