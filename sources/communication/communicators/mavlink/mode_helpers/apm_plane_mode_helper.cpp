#include "apm_plane_mode_helper.h"

// Qt
#include <QMap>

namespace
{
    QMap<quint32, domain::vehicle::Mode> modeMap =
    {
        { 0, domain::vehicle::Mode::Manual },
        { 1, domain::vehicle::Mode::Circle },
        { 2, domain::vehicle::Mode::Stabilize },
        { 4, domain::vehicle::Mode::Acro },
        { 5, domain::vehicle::Mode::CtrlByAttitude },
        { 6, domain::vehicle::Mode::CtrlByAltitude },
        { 7, domain::vehicle::Mode::Cruise },
        { 8, domain::vehicle::Mode::Autotune },
        { 10, domain::vehicle::Mode::Mission },
        { 11, domain::vehicle::Mode::Return },
        { 12, domain::vehicle::Mode::Loiter },
        { 14, domain::vehicle::Mode::Avoid },
        { 15, domain::vehicle::Mode::Guided },
        { 16, domain::vehicle::Mode::Init }
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
//        domain::vehicle::Mode::CtrlByAltitude,
//        domain::vehicle::Mode::Acro,
//        domain::vehicle::Mode::Autotune,
//        domain::vehicle::Mode::Cruise,
        domain::vehicle::Mode::CtrlByAttitude,
        domain::vehicle::Mode::Mission,
        domain::vehicle::Mode::Return,
        domain::vehicle::Mode::Loiter,
        domain::vehicle::Mode::Circle,
        domain::vehicle::Mode::Guided
    };
}
