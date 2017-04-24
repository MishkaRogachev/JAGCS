#ifndef MAVLINK_MODE_HELPER_H
#define MAVLINK_MODE_HELPER_H

// MAVLink
#include <mavlink.h>

// Qt
#include <QCoreApplication>

namespace comm
{
    QString decodeApmMode(uint8_t type, uint32_t mode)
    {
        switch (type)
        {
        case MAV_TYPE_FIXED_WING:
            if (mode == 0) return qApp->translate("MAVLINK", "MANUAL");
            if (mode == 1) return qApp->translate("MAVLINK", "CIRCLE");
            if (mode == 2) return qApp->translate("MAVLINK", "STABILIZE");
            if (mode == 3) return qApp->translate("MAVLINK", "TRAINING");
            if (mode == 4) return qApp->translate("MAVLINK", "ACRO");
            if (mode == 5) return qApp->translate("MAVLINK", "FBWA");
            if (mode == 6) return qApp->translate("MAVLINK", "FBWB");
            if (mode == 7) return qApp->translate("MAVLINK", "CRUISE");
            if (mode == 8) return qApp->translate("MAVLINK", "AUTOTUNE");
            if (mode == 10) return qApp->translate("MAVLINK", "AUTO");
            if (mode == 11) return qApp->translate("MAVLINK", "RETURN");
            if (mode == 12) return qApp->translate("MAVLINK", "LOITER");
            if (mode == 14) return qApp->translate("MAVLINK", "AVOID ADSB");
            if (mode == 15) return qApp->translate("MAVLINK", "GUIDED");
            if (mode == 16) return qApp->translate("MAVLINK", "INITIALISE");
            if (mode == 17) return qApp->translate("MAVLINK", "QSTABILIZE");
            if (mode == 18) return qApp->translate("MAVLINK", "QHOVER");
            if (mode == 19) return qApp->translate("MAVLINK", "QLOITER");
            if (mode == 20) return qApp->translate("MAVLINK", "QLAND");
            if (mode == 21) return qApp->translate("MAVLINK", "QRETURN");
            return qApp->translate("MAVLINK", "APM PLANE NONE");
        case MAV_TYPE_TRICOPTER:
        case MAV_TYPE_QUADROTOR:
        case MAV_TYPE_HEXAROTOR:
        case MAV_TYPE_OCTOROTOR:
        case MAV_TYPE_COAXIAL:
        case MAV_TYPE_HELICOPTER:
            if (mode == 0) return qApp->translate("MAVLINK", "STABILIZE");
            if (mode == 1) return qApp->translate("MAVLINK", "ACRO");
            if (mode == 2) return qApp->translate("MAVLINK", "ALT HOLD");
            if (mode == 3) return qApp->translate("MAVLINK", "AUTO");
            if (mode == 4) return qApp->translate("MAVLINK", "GUIDED");
            if (mode == 5) return qApp->translate("MAVLINK", "LOITER");
            if (mode == 6) return qApp->translate("MAVLINK", "RETURN");
            if (mode == 7) return qApp->translate("MAVLINK", "CIRCLE");
            if (mode == 9) return qApp->translate("MAVLINK", "LAND");
            if (mode == 11) return qApp->translate("MAVLINK", "DRIFT");
            if (mode == 13) return qApp->translate("MAVLINK", "SPORT");
            if (mode == 14) return qApp->translate("MAVLINK", "FLIP");
            if (mode == 15) return qApp->translate("MAVLINK", "AUTOTUNE");
            if (mode == 16) return qApp->translate("MAVLINK", "POS HOLD");
            if (mode == 17) return qApp->translate("MAVLINK", "BRAKE");
            if (mode == 18) return qApp->translate("MAVLINK", "THROW");
            if (mode == 19) return qApp->translate("MAVLINK", "AVOID ADSB");
            if (mode == 20) return qApp->translate("MAVLINK", "GUIDED NO SNS");
        default:
            break;
        }

        return qApp->translate("MAVLINK", "APM NONE");
    }

    QString decodePx4Mode(uint32_t mode)
    {
        uint8_t mainMode = (mode >> 0) & 0xFF;
        uint8_t autoMode = (mode >> 8) & 0xFF;

        switch (mainMode)
        {
        case 1: return qApp->translate("MAVLINK", "MANUAL");
        case 2: return qApp->translate("MAVLINK", "ALT CTL");
        case 3: return qApp->translate("MAVLINK", "POS CTL");
        case 4:
            if (autoMode == 1) return qApp->translate("MAVLINK", "READY");
            if (autoMode == 2) return qApp->translate("MAVLINK", "TAKEOFF");
            if (autoMode == 3) return qApp->translate("MAVLINK", "LOITER");
            if (autoMode == 4) return qApp->translate("MAVLINK", "MISSION");
            if (autoMode == 5) return qApp->translate("MAVLINK", "RETURN");
            if (autoMode == 6) return qApp->translate("MAVLINK", "LAND");
            if (autoMode == 7) return qApp->translate("MAVLINK", "RTGS");
            if (autoMode == 8) return qApp->translate("MAVLINK", "FOLLOW");
            return qApp->translate("MAVLINK", "PX4 AUTO NONE");
        case 5: return qApp->translate("MAVLINK", "ACRO");
        case 6: return qApp->translate("MAVLINK", "OFFBOARD");
        case 7: return qApp->translate("MAVLINK", "STABILIZED");
        case 8: return qApp->translate("MAVLINK", "RATTITUDE");
        }

        return qApp->translate("MAVLINK", "PX4 NONE");
    }

    QString decodeCustomMode(uint8_t ap, uint8_t type, uint32_t mode)
    {
        switch (ap)
        {
        case MAV_AUTOPILOT_ARDUPILOTMEGA:
            return decodeApmMode(type, mode);
        case MAV_AUTOPILOT_PX4:
            return decodePx4Mode(mode);
        default:
            break;
        }

        return qApp->translate("MAVLINK", "NONE");
    }
}

#endif // MAVLINK_MODE_HELPER_H
