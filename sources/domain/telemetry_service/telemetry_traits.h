#ifndef TELEMETRY_TRAITS_H
#define TELEMETRY_TRAITS_H

// Qt
#include <QVariant>

// root
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

namespace domain
{
    enum class TelemetryId
    {
        Root = 1,

        Status = 100,
        Online = 101,
        Armed = 102,
        Mode = 103,

        Present = 200,
        Enabled = 201,
        Operational = 202,

        Position = 300,
        Coordinate = 301,
        Direction = 302,
        Home = 400,

        Altitude = 501,
        Climb = 502,
        Course = 503,
        Heading = 504,
        Speed = 505,
        Groundspeed = 506,
        IndicatedAirspeed = 507,
        TrueAirspeed = 508,
        Temperature = 509,

        Ahrs = 1000,
        Pitch = 1001,
        Roll = 1002,
        Yaw = 1003,
        PitchSpeed = 1004,
        RollSpeed = 1005,
        YawSpeed = 1006,

        Satellite = 2000,
        Fix = 2002,
        Eph = 2003,
        Epv = 2004,
        Time = 2005,
        SatellitesVisible = 2006,

        Compass = 3000,

        Barometric = 4000,
        AbsPressure = 4001,
        DiffPressure = 4002,

        Pitot = 5000,

        Navigator = 6000,
        TargetBearing = 6001,
        TargetDistance = 6002,
        TrackError = 6003,
        AltitudeError = 6004,
        DesiredPitch = 6005,
        DesiredRoll = 6006,
        DesiredHeading = 6007,

        PowerSystem = 7000,
        Throttle = 7001,

        Wind = 8000,
    };

    using TelemetryList = QList<TelemetryId>;
    using TelemetryMap = QMap<TelemetryId, QVariant>;
}

#endif // TELEMETRY_TRAITS_H
