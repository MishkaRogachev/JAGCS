#include "px4_mode_helper.h"

// Qt
#include <QMap>

using namespace comm;

namespace
{
    QMap<uint32_t, domain::Mode> modeMap =
    {
        { 0x0000, domain::Mode::Manual },
        { 0x0001, domain::Mode::CtrlByAltitude },
        { 0x0002, domain::Mode::HoldPosition },
        { 0x0003, domain::Mode::HoldPosition },
        { 0x0204, domain::Mode::Takeoff },
        { 0x0304, domain::Mode::Loiter },
        { 0x0404, domain::Mode::Mission },
        { 0x0504, domain::Mode::Return },
        { 0x0604, domain::Mode::Landing },
        { 0x0704, domain::Mode::Return },
        { 0x0804, domain::Mode::Follow },
        { 0x0007, domain::Mode::Stabilize }
    };
}

Px4ModeHelper::Px4ModeHelper():
    IModeHelper()
{}

quint32 Px4ModeHelper::modeToCustomMode(domain::Mode mode)
{
    return ::modeMap.key(mode, 0);
}

domain::Mode Px4ModeHelper::customModeToMode(quint32 mode)
{
    return ::modeMap.value(mode, domain::Mode::None);
}
