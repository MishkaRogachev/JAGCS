#include "px4_mode_helper.h"

// Qt
#include <QMap>

using namespace data_source;

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

    QMap<uint32_t, Telemetry::VehicleMode> modeMap =
    {
        { Px4CustomMode({ { 0, PX4_MODE_MANUAL, 0 } }).mode,
          Telemetry::ManualMode },
        { Px4CustomMode({ { 0, PX4_MODE_STABILIZED, 0 } }).mode,
          Telemetry::StabilizeMode },
        { Px4CustomMode({ { 0, PX4_MODE_ACRO, 0 } }).mode,
          Telemetry::AcroMode },
        { Px4CustomMode({ { 0, PX4_MODE_RATTITUDE, 0 } }).mode,
          Telemetry::RattitudeMode },
        { Px4CustomMode({ { 0, PX4_MODE_ALTCTL, 0 } }).mode,
          Telemetry::AltCtrlMode },
        { Px4CustomMode({ { 0, PX4_MODE_POSCTL, 0 } }).mode,
          Telemetry::PosCtrlMode },
        { Px4CustomMode({ { 0, PX4_MODE_AUTO, PX4_MODE_AUTO_LOITER } }).mode,
          Telemetry::LoiterMode },
        { Px4CustomMode({ { 0, PX4_MODE_AUTO, PX4_MODE_AUTO_MISSION } }).mode,
          Telemetry::MissionMode },
        { Px4CustomMode({ { 0, PX4_MODE_AUTO, PX4_MODE_AUTO_RTL } }).mode,
          Telemetry::ReturnMode },
        { Px4CustomMode({ { 0, PX4_MODE_AUTO, PX4_MODE_AUTO_FOLLOW } }).mode,
          Telemetry::FollowMode },
        { Px4CustomMode({ { 0, PX4_MODE_AUTO, PX4_MODE_AUTO_LAND } }).mode,
          Telemetry::LandingMode },
        { Px4CustomMode({ { 0, PX4_MODE_AUTO, PX4_MODE_AUTO_TAKEOFF } }).mode,
          Telemetry::TakeoffMode }
    };
}

Px4ModeHelper::Px4ModeHelper():
    IModeHelper()
{}

int Px4ModeHelper::modeToCustomMode(Telemetry::VehicleMode mode)
{
    return ::modeMap.key(mode, -1);
}

Telemetry::VehicleMode Px4ModeHelper::customModeToMode(quint32 mode)
{
    return ::modeMap.value(mode, Telemetry::NoneMode);
}

QList<Telemetry::VehicleMode> Px4ModeHelper::availableModes() const
{
    return ::modeMap.values();
}
