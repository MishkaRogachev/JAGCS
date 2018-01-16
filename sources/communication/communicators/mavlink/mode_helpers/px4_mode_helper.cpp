#include "px4_mode_helper.h"

// Qt
#include <QMap>

using namespace comm;

namespace
{
    QMap<uint32_t, domain::vehicle::Mode> modeMap =
    {
        { 0x0000, domain::vehicle::Mode::Manual },
        { 0x0001, domain::vehicle::Mode::CtrlByAltitude },
        { 0x0002, domain::vehicle::Mode::HoldPosition },
        { 0x0003, domain::vehicle::Mode::HoldPosition },
        { 0x0204, domain::vehicle::Mode::Takeoff },
        { 0x0304, domain::vehicle::Mode::Loiter },
        { 0x0404, domain::vehicle::Mode::Mission },
        { 0x0504, domain::vehicle::Mode::Return },
        { 0x0604, domain::vehicle::Mode::Landing },
        { 0x0704, domain::vehicle::Mode::Return },
        { 0x0804, domain::vehicle::Mode::Follow },
        { 0x0007, domain::vehicle::Mode::Stabilize }
    };
}

Px4ModeHelper::Px4ModeHelper():
    IModeHelper()
{}

int Px4ModeHelper::modeToCustomMode(domain::vehicle::Mode mode)
{
    return ::modeMap.key(mode, -1);
}

domain::vehicle::Mode Px4ModeHelper::customModeToMode(quint32 mode)
{
    return ::modeMap.value(mode, domain::vehicle::Mode::None);
}

QList<domain::vehicle::Mode> Px4ModeHelper::availableModes() const
{
    return ::modeMap.values();
}
