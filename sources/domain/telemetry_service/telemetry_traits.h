#ifndef TELEMETRY_TRAITS_H
#define TELEMETRY_TRAITS_H

// Qt
#include <QString>

namespace telemetry
{
    const QString online = "online";
    const QString armed = "armed";
    const QString mode = "mode";

    const QString present = "present";
    const QString enabled = "enabled";
    const QString operational = "operational";

    const QString pitch = "pitch";
    const QString roll = "roll";
    const QString yaw = "yaw";
    const QString heading = "heading";
    const QString course = "course";

    const QString indicatedAirspeed = "indicatedAirspeed";
    const QString trueAirspeed = "trueAirspeed";
    const QString groundspeed = "groundspeed";
    const QString speed = "speed";

    const QString altitude = "altitude";
    const QString climb = "climb";

    const QString throttle = "throttle";

    const QString coordinate = "coordinate";
    const QString direction = "direction";

    const QString fix = "fix";
    const QString eph = "eph";
    const QString epv = "epv";
    const QString time = "time";

    const QString home = "home";
    const QString position = "position";

    const QString ahrs = "ahrs";
    const QString sns = "sns";
    const QString baro = "baro";
    const QString navi = "navi";
    const QString powerSystem = "powerSystem";
    const QString wind = "wind";

    const QString targetBearing = "targetBearing";
    const QString targetDistance = "targetDistance";
    const QString trackError = "trackError";
    const QString altitudeError = "altitudeError";

    const QString desiredPitch = "desiredPitch";
    const QString desiredRoll = "desiredRoll";
    const QString desiredHeading = "desiredHeading";

    enum class SnsFix
    {
        NoGps,
        NoFix,
        Fix2D,
        Fix3D
    };
}

#endif // TELEMETRY_TRAITS_H
