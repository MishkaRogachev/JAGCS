#include "apm_copter_mode_helper.h"

// Qt
#include <QMap>

namespace
{
    QMap<quint32, domain::vehicle::Mode> modeMap =
    {
        { 0, domain::vehicle::Mode::Stabilize },
        { 1, domain::vehicle::Mode::Acro },
        { 2, domain::vehicle::Mode::CtrlByAltitude },
        { 3, domain::vehicle::Mode::Mission },
        { 4, domain::vehicle::Mode::Guided },
        { 5, domain::vehicle::Mode::Loiter },
        { 6, domain::vehicle::Mode::Return },
        { 7, domain::vehicle::Mode::Circle },
        { 9, domain::vehicle::Mode::Landing },
        { 15, domain::vehicle::Mode::Autotune },
        { 16, domain::vehicle::Mode::HoldPosition },
        { 18, domain::vehicle::Mode::Throw },
        { 19, domain::vehicle::Mode::Avoid }
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
    return {
        domain::vehicle::Mode::Stabilize,
        domain::vehicle::Mode::HoldPosition,
        domain::vehicle::Mode::CtrlByAltitude,
        domain::vehicle::Mode::Loiter,
        domain::vehicle::Mode::Mission,
        domain::vehicle::Mode::Throw,
        domain::vehicle::Mode::Circle,
        domain::vehicle::Mode::Follow,
        domain::vehicle::Mode::Landing
    };
}
