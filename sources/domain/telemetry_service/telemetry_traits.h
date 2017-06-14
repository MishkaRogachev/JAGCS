#ifndef TELEMETRY_TRAITS_H
#define TELEMETRY_TRAITS_H

// Qt
#include <QString>

// mav
//  |-status
//  |  |-online                         bool
//  |  |-armed                          bool
//  |  |-mode                           string
//  |-position
//  |  |-coordinate                     coordinate
//  |  |-direction                      direction
//  |-home
//  |  |-coordinate                     coordinate
//  |  |-direction                      direction
//  |-ahrs
//  |  |-present                        bool
//  |  |-enabled                        bool
//  |  |-operational                    bool
//  |  |-pitch                          real
//  |  |-roll                           real
//  |  |-yaw                            real
//  |  |-pitchspeed                     real
//  |  |-rollspeed                      real
//  |  |-yawspeed                       real
//  |-satellite
//  |  |-present                        bool
//  |  |-enabled                        bool
//  |  |-operational                    bool
//  |  |-fix                            int
//  |  |-coordinate                     coordinate
//  |  |-groundspeed                    real
//  |  |-course                         real
//  |  |-altitude                       real
//  |  |-climb                          real
//  |  |-eph                            int
//  |  |-epv                            int
//  |  |-time                           time
//  |  |-satellitesVisible              int
//  |-compass
//  |  |-present                        bool
//  |  |-enabled                        bool
//  |  |-operational                    bool
//  |  |-heading                        real
//  |-barometric
//  |  |-present                        bool
//  |  |-enabled                        bool
//  |  |-operational                    bool
//  |  |-altitude                       real
//  |  |-climb                          real
//  |  |-absPressure                    int
//  |  |-diffPressure                   int
//  |  |-temperature                    real
//  |-pitot
//  |  |-present                        bool
//  |  |-enabled                        bool
//  |  |-operational                    bool
//  |  |-trueAirspeed                   real
//  |  |-indicatedAirspeed              real
// TODO: rangefinder
//  |-navigator
//  |  |-targetBearing                  real
//  |  |-targetDistance                 real
//  |  |-trackError                     real
//  |  |-altitudeError                  real
//  |  |-desiredPitch                   real
//  |  |-desiredRoll                    real
//  |  |-desiredHeading                 real
//  |-powerSystem
//  |  |-throttle                       int
//  |-wind
//  |  |-yaw                            real
//  |  |-speed                          real
//  |  |-climb                          real

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
    const QString pitchspeed = "pitchspeed";
    const QString rollspeed = "rollspeed";
    const QString yawspeed = "yawspeed";
    const QString heading = "heading";
    const QString course = "course";

    const QString indicatedAirspeed = "indicatedAirspeed";
    const QString trueAirspeed = "trueAirspeed";
    const QString groundspeed = "groundspeed";
    const QString speed = "speed";

    const QString altitude = "altitude";
    const QString climb = "climb";

    const QString absPressure = "absPressure";
    const QString diffPressure = "diffPressure";
    const QString temperature = "temperature";

    const QString throttle = "throttle";

    const QString coordinate = "coordinate";
    const QString direction = "direction";

    const QString fix = "fix";
    const QString eph = "eph";
    const QString epv = "epv";
    const QString time = "time";
    const QString satellitesVisible = "satellitesVisible";

    const QString status = "status";

    const QString position = "position";
    const QString home = "home";

    const QString ahrs = "ahrs";
    const QString satellite = "satellite";
    const QString compass = "compass";
    const QString barometric = "barometric";
    const QString pitot = "pitot";
    const QString navigator = "navigator";
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
