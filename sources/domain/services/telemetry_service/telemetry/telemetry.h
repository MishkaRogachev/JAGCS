#ifndef TELEMETRY_NODE_H
#define TELEMETRY_NODE_H

//Internal
#include <QObject>
#include <QMap>

// mav
//  |-Status
//  |  |-Armed                          bool
//  |  |-Auto                           bool
//  |  |-Guided                         bool
//  |  |-Stabilized                     bool
//  |  |-Manual                         bool
//  |  |-Mode                           string
//  |  |-State                          SystemState
//  |-Position
//  |  |-Coordinate                     coordinate
//  |  |-Direction                      direction
//  |-HomePosition
//  |  |-Coordinate                     coordinate
//  |  |-Direction                      direction
//  |  |-Altitude                       altitude
//  |-Ahrs
//  |  |-Present                        bool
//  |  |-Enabled                        bool
//  |  |-Operational                    bool
//  |  |-Pitch                          real
//  |  |-Roll                           real
//  |  |-Yaw                            real
//  |  |-Pitchspeed                     real
//  |  |-Rollspeed                      real
//  |  |-Yawspeed                       real
//  |  |-Accel
//  |  |  |-Present                     bool
//  |  |  |-Enabled                     bool
//  |  |  |-Operational                 bool
//  |  |-Gyro
//  |  |  |-Present                     bool
//  |  |  |-Enabled                     bool
//  |  |  |-Operational                 bool
//  |-Satellite
//  |  |-Present                        bool
//  |  |-Enabled                        bool
//  |  |-Operational                    bool
//  |  |-Fix                            int
//  |  |-Coordinate                     coordinate
//  |  |-Groundspeed                    real
//  |  |-Course                         real
//  |  |-Altitude                       real
//  |  |-Climb                          real
//  |  |-Eph                            int
//  |  |-Epv                            int
//  |  |-Time                           time
//  |  |-SatellitesVisible              int
//  |-Compass
//  |  |-Present                        bool
//  |  |-Enabled                        bool
//  |  |-Operational                    bool
//  |  |-Heading                        real
//  |-Barometric
//  |  |-Present                        bool
//  |  |-Enabled                        bool
//  |  |-Operational                    bool
//  |  |-Altitude                       real
//  |  |-Climb                          real
//  |  |-AbsPressure                    int
//  |  |-DiffPressure                   int
//  |  |-Temperature                    real
//  |-Pitot
//  |  |-Present                        bool
//  |  |-Enabled                        bool
//  |  |-Operational                    bool
//  |  |-TrueAirspeed                   real
//  |  |-IndicatedAirspeed              real
//  |-Rangefinder
//  |  |-Present                        bool
//  |  |-Enabled                        bool
//  |  |-Operational                    bool
//  |  |-Elevation                      real
//  |  |-Voltage                        real
//  |-Navigator
//  |  |-TargetBearing                  real
//  |  |-TargetDistance                 real
//  |  |-TrackError                     real
//  |  |-AltitudeError                  real
//  |  |-DesiredPitch                   real
//  |  |-DesiredRoll                    real
//  |  |-DesiredHeading                 real
//  |-PowerSystem
//  |  |-Throttle                       int
//  |-Battery
//  |  |-Present                        bool
//  |  |-Enabled                        bool
//  |  |-Operational                    bool
//  |  |-Voltage                        real
//  |  |-Current                        real
//  |  |-Percentage                     int
//  |-Wind
//  |  |-Yaw                            real
//  |  |-Speed                          real
//  |  |-Climb                          real
// radio
//  |-Rssi                              real
//  |-Noise                             int
//  |-RemoteRssi                        real
//  |-RemoteNoise                       int
//  |-Errors                            int
//  |-Fixed                             int

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
            Armed = 102,
            Auto = 103,
            Guided = 104,
            Stabilized = 105,
            Manual = 106,
            Mode = 110,
            State = 120,

            Present = 200,
            Enabled = 201,
            Operational = 202,

            Position = 300,
            Coordinate = 301,
            Direction = 302,

            HomePosition = 400,

            Altitude = 501,
            Height = 502,
            Climb = 503,
            Course = 504,
            Heading = 505,
            Speed = 506,
            Groundspeed = 507,
            IndicatedAirspeed = 508,
            TrueAirspeed = 509,
            Temperature = 510,
            Voltage = 511,
            Current = 512,
            Percentage = 513,

            Ahrs = 1000,
            Pitch = 1001,
            Roll = 1002,
            Yaw = 1003,
            PitchSpeed = 1004,
            RollSpeed = 1005,
            YawSpeed = 1006,
            Accel = 1100,
            Gyro = 1200,

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

            Rangefinder = 6000,

            Navigator = 7000,
            TargetBearing = 7001,
            TargetDistance = 7002,
            TrackError = 7003,
            AltitudeError = 7004,
            DesiredPitch = 7005,
            DesiredRoll = 7006,
            DesiredHeading = 7007,

            PowerSystem = 8000,
            Throttle = 8001,

            Battery = 9000,
            ConsumedCharge = 9001,

            Rssi = 10001,
            Noise = 10002,
            RemoteRssi = 10003,
            RemoteNoise = 10004,
            Errors = 10005,
            Fixed = 10006,

            Wind = 11000,
        };

        enum SystemState
        {
            UnknownState,
            Boot,
            Calibrating,
            Standby,
            Active,
            Critical,
            Emergency
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
        Q_ENUM(SystemState)
    };
}

#endif // TELEMETRY_NODE_H
