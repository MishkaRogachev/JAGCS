#ifndef MAVLINK_MODE_HELPER_H
#define MAVLINK_MODE_HELPER_H

// MAVLink
#include <mavlink.h>

// Internal
#include "modes.h"

namespace comm
{
    inline domain::Mode decodeApmMode(uint8_t type, uint32_t mode)
    {
        switch (type)
        {
        case MAV_TYPE_FIXED_WING:
            if (mode == 0) return domain::Mode::Manual;
            if (mode == 1) return domain::Mode::Circle;
            if (mode == 2) return domain::Mode::Stabilize;
            if (mode == 4) return domain::Mode::Acro;
            if (mode == 5) return domain::Mode::CtrlByAttitude;
            if (mode == 6) return domain::Mode::CtrlByAltitude;
            if (mode == 7) return domain::Mode::Cruise;
            if (mode == 8) return domain::Mode::Autotune;
            if (mode == 10) return domain::Mode::Mission;
            if (mode == 11) return domain::Mode::Return;
            if (mode == 12) return domain::Mode::Loiter;
            if (mode == 14) return domain::Mode::Avoid;
            if (mode == 15) return domain::Mode::Guided;
            if (mode == 16) return domain::Mode::Init;
            break;
        case MAV_TYPE_TRICOPTER:
        case MAV_TYPE_QUADROTOR:
        case MAV_TYPE_HEXAROTOR:
        case MAV_TYPE_OCTOROTOR:
        case MAV_TYPE_COAXIAL:
        case MAV_TYPE_HELICOPTER:
            if (mode == 0) return domain::Mode::Stabilize;
            if (mode == 1) return domain::Mode::Acro;
            if (mode == 2) return domain::Mode::CtrlByAltitude;
            if (mode == 3) return domain::Mode::Mission;
            if (mode == 4) return domain::Mode::Guided;
            if (mode == 5) return domain::Mode::Loiter;
            if (mode == 6) return domain::Mode::Return;
            if (mode == 7) return domain::Mode::Circle;
            if (mode == 9) return domain::Mode::Landing;
            if (mode == 15) return domain::Mode::Autotune;
            if (mode == 16) return domain::Mode::HoldPosition;
            if (mode == 18) return domain::Mode::Throw;
            if (mode == 19) return domain::Mode::Avoid;
            break;
        default:
            break;
        }

        return domain::Mode::None;
    }

    inline domain::Mode decodePx4Mode(uint32_t mode)
    {
        uint8_t mainMode = (mode >> 0) & 0xFF;
        uint8_t autoMode = (mode >> 8) & 0xFF;

        switch (mainMode)
        {
        case 1: return domain::Mode::Manual;
        case 2: return domain::Mode::CtrlByAltitude;
        case 3: return domain::Mode::HoldPosition;
        case 4:
            if (autoMode == 2) return domain::Mode::Takeoff;
            if (autoMode == 3) return domain::Mode::Loiter;
            if (autoMode == 4) return domain::Mode::Mission;
            if (autoMode == 5) return domain::Mode::Return;
            if (autoMode == 6) return domain::Mode::Landing;
            if (autoMode == 7) return domain::Mode::Return;
            if (autoMode == 8) return domain::Mode::Follow;;
            break;
        case 7: return domain::Mode::Stabilize;
        default:
            break;
        }

        return domain::Mode::None;
    }

    inline domain::Mode decodeCustomMode(uint8_t ap, uint8_t type, uint32_t mode)
    {
        switch (ap)
        {
        case MAV_AUTOPILOT_ARDUPILOTMEGA:
            return decodeApmMode(type, mode);
        case MAV_AUTOPILOT_PX4:
            return decodePx4Mode(mode);
        default:
            return domain::Mode::None;
        }
    }
}

#endif // MAVLINK_MODE_HELPER_H
