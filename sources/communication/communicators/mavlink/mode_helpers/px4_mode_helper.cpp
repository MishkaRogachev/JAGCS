#include "px4_mode_helper.h"

// Qt
#include <QMap>

using namespace comm;
using namespace domain::vehicle;

namespace
{
    enum PX4_MODE
    {
        PX4_MODE_MANUAL             = 1,
        PX4_MODE_ALTCTL             = 2,
        PX4_MODE_POSCTL             = 3,
        PX4_MODE_AUTO               = 4,
        PX4_MODE_ACRO               = 5,
        PX4_MODE_OFFBOARD           = 6,
        PX4_MODE_STABILIZED         = 7,
        PX4_MODE_RATTITUDE          = 8,
        PX4_MODE_SIMPLE             = 9
    };

    enum PX4_MODE_AUTO
    {
        PX4_MODE_AUTO_READY          = 1,
        PX4_MODE_AUTO_TAKEOFF        = 2,
        PX4_MODE_AUTO_LOITER         = 3,
        PX4_MODE_AUTO_MISSION        = 4,
        PX4_MODE_AUTO_RTL            = 5,
        PX4_MODE_AUTO_LAND           = 6,
        PX4_MODE_AUTO_RTGS           = 7,
        PX4_MODE_AUTO_FOLLOW  = 8
    };

    union Px4CustomMode
    {
        struct
        {
            uint16_t reserved;
            uint8_t main_mode;
            uint8_t sub_mode;
        };

        uint32_t mode;
    };

    QMap<uint32_t, domain::vehicle::Mode> modeMap =
    {
        { Px4CustomMode({ 0, PX4_MODE_MANUAL, 0 }).mode,                        Mode::Manual },
        { Px4CustomMode({ 0, PX4_MODE_STABILIZED, 0 }).mode,                    Mode::Stabilize },
        { Px4CustomMode({ 0, PX4_MODE_ACRO, 0 }).mode,                          Mode::Acro },
        { Px4CustomMode({ 0, PX4_MODE_RATTITUDE, 0 }).mode,                     Mode::Rattitude },
        { Px4CustomMode({ 0, PX4_MODE_ALTCTL, 0 }).mode,                        Mode::AltCtrl },
        { Px4CustomMode({ 0, PX4_MODE_POSCTL, 0 }).mode,                        Mode::PosCtrl },
        { Px4CustomMode({ 0, PX4_MODE_AUTO, PX4_MODE_AUTO_LOITER }).mode,       Mode::Loiter },
        { Px4CustomMode({ 0, PX4_MODE_AUTO, PX4_MODE_AUTO_MISSION }).mode,      Mode::Mission },
        { Px4CustomMode({ 0, PX4_MODE_AUTO, PX4_MODE_AUTO_RTL }).mode,          Mode::Return },
        { Px4CustomMode({ 0, PX4_MODE_AUTO, PX4_MODE_AUTO_FOLLOW }).mode,       Mode::Follow },
        { Px4CustomMode({ 0, PX4_MODE_AUTO, PX4_MODE_AUTO_LAND }).mode,         Mode::Landing },
        { Px4CustomMode({ 0, PX4_MODE_AUTO, PX4_MODE_AUTO_TAKEOFF }).mode,      Mode::Takeoff }
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
