#ifndef TELEMETRY_NODE_H
#define TELEMETRY_NODE_H

//Internal
#include <QObject>
#include <QMap>

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
    class Telemetry: public QObject
    {
        Q_OBJECT

    public:
        enum TelemetryId
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

        Telemetry(TelemetryId id, Telemetry* parentNode = nullptr);
        ~Telemetry() override;

        TelemetryId id() const;

        QVariant parameter(TelemetryId id) const;
        QMap<TelemetryId, QVariant> parameters() const;

        QList<TelemetryId> changedParameterKeys() const;
        QMap<TelemetryId, QVariant> takeChangedParameters();

        Telemetry* parentNode() const;
        Telemetry* childNode(TelemetryId id);
        Telemetry* childNode(const TelemetryList& path);
        QList<Telemetry*> childNodes() const;

    public slots:
        void setParameter(TelemetryId id, const QVariant& value);
        void setParameter(const QList<TelemetryId>& path, const QVariant& value);
        void notify();

    signals:
        void parametersChanged(TelemetryMap parameters);

    protected:
        void addChildNode(Telemetry* childNode);
        void removeChildNode(Telemetry* childNode);

    private:
        const TelemetryId m_id;
        TelemetryMap m_parameters;
        TelemetryList m_changedParameters;

        Telemetry* const m_parentNode;
        QMap<TelemetryId, Telemetry*> m_childNodes;

        Q_ENUM(TelemetryId)
    };
}

#endif // TELEMETRY_NODE_H
