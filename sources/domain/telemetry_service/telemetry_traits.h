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

    const QString indicatedAirspeed = "indicatedAirspeed";
    const QString trueAirspeed = "trueAirspeed";
    const QString groundspeed = "groundspeed";

    const QString altitude = "altitude";
    const QString climb = "climb";

    const QString coordinate = "coordinate";
    const QString direction = "direction";

    const QString home = "home";
    const QString ahrs = "ahrs";
    const QString sns = "sns";
    const QString baro = "baro";
    const QString navi = "navi";
    const QString power_system = "power_system";

    const QString targetBearing = "targetBearing";
    const QString targetDistance = "targetDistance";
    const QString trackError = "trackError";
    const QString altitudeError = "altitudeError";

    const QString desiredPitch = "desiredPitch";
    const QString desiredRoll = "desiredRoll";
    const QString desiredHeading = "desiredHeading";
}

#endif // TELEMETRY_TRAITS_H
