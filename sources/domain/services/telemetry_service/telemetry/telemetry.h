#ifndef TELEMETRY_NODE_H
#define TELEMETRY_NODE_H

//Internal
#include <QObject>
#include <QMap>

// TODO: unit support

// mav
//  |-Flight
//  |  |-Uid                            uint64
//  |  |-Time                           QDateTime
//  |-System
//  |  |-Armed                          bool
//  |  |-Auto                           bool
//  |  |-Guided                         bool
//  |  |-Stabilized                     bool
//  |  |-Manual                         bool
//  |  |-Mode                           Mode
//  |  |-AvailableModes                 QList<Modes>
//  |  |-State                          SystemState
//  |-Position
//  |  |-Coordinate                     QGeoCoordinate
//  |  |-Direction                      QVector3D
//  |-HomePosition
//  |  |-Coordinate                     QGeoCoordinate
//  |  |-Direction                      QVector3D
//  |  |-Altitude                       real
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
//  |  |-Vibration                      QVector3D
//  |  |-Accel
//  |  |  |-Present                     bool
//  |  |  |-Enabled                     bool
//  |  |  |-Operational                 bool
//  |  |  |-Acceleration                QVector3D
//  |  |-Gyro
//  |  |  |-Present                     bool
//  |  |  |-Enabled                     bool
//  |  |  |-Operational                 bool
//  |  |  |-AngularSpeed                QVector3D
//  |  |-Compass
//  |     |-Present                     bool
//  |     |-Enabled                     bool
//  |     |-Operational                 bool
//  |     |-Heading                     real
//  |     |-MagneticField               QVector3D
//  |-Satellite
//  |  |-Present                        bool
//  |  |-Enabled                        bool
//  |  |-Operational                    bool
//  |  |-Fix                            int
//  |  |-Coordinate                     QGeoCoordinate
//  |  |-Groundspeed                    real
//  |  |-Course                         real
//  |  |-Altitude                       real
//  |  |-Climb                          real
//  |  |-Eph                            int
//  |  |-Epv                            int
//  |  |-Time                           QTime
//  |  |-SatellitesVisible              int
//  |  |-SatelliteInfos                 QList<SatelliteInfo>
//  |-Barometric
//  |  |-Present                        bool
//  |  |-Enabled                        bool
//  |  |-Operational                    bool
//  |  |-AltitudeMsl                    real
//  |  |-AltitudeRelative               real
//  |  |-AltitudeTerrain                real
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
//  |  |-Distance                       real
//  |  |-TrackError                     real
//  |  |-AltitudeError                  real
//  |-FlightControl
//  |  |-DesiredPitch                   real
//  |  |-DesiredRoll                    real
//  |  |-DesiredHeading                 real
//  |  |-Coordinate                     QGeoCoordinate
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
//  |-LandingSystem
//  |  |-Distance                       real
//  |  |-DeviationX                     real
//  |  |-DeviationY                     real
//  |  |-SizeX                          real
//  |  |-SizeY                          real
//  |  |-Coordinate                     coordinate
// radio
//  |-Rssi                              real
//  |-Noise                             int
//  |-RemoteRssi                        real
//  |-RemoteNoise                       int
//  |-Errors                            int
//  |-Fixed                             int

// TODO: Present-Enabled-Operational bools replace with enum

namespace domain
{
    class Telemetry: public QObject
    {
        Q_OBJECT

    public:
        enum TelemetryId
        {
            Root = 1,

            Flight = 10,
            Uid = 11,
            Time = 12,

            System = 100,
            Armed = 102,
            Auto = 103,
            Guided = 104,
            Stabilized = 105,
            Manual = 106,
            Mode = 110,
            AvailableModes = 120,
            State = 130,

            Present = 200,
            Enabled = 201,
            Operational = 202,

            Position = 300,
            Coordinate = 301,
            Direction = 302,
            Distance = 303,

            HomePosition = 400,

            Altitude = 501,
            Height = 502,
            Climb = 503,
            Course = 504,
            Heading = 505,
            Speed = 506,
            Groundspeed = 507,
            Temperature = 508,
            Voltage = 509,
            Current = 510,
            Percentage = 511,

            Ahrs = 1000,
            Pitch = 1001,
            Roll = 1002,
            Yaw = 1003,
            PitchSpeed = 1004,
            RollSpeed = 1005,
            YawSpeed = 1006,
            Vibration = 1010,
            Accel = 1100,
            Acceleration = 1101,
            Gyro = 1200,
            AngularSpeed = 1201,
            Compass = 1300,
            MagneticField = 1301,

            Satellite = 2000,
            Fix = 2001,
            Eph = 2002,
            Epv = 2003,
            SatellitesVisible = 2004,
            SatelliteInfos = 2005,

            Barometric = 3000,
            AbsPressure = 3001,
            DiffPressure = 3002,
            AltitudeMsl = 3003,
            AltitudeRelative = 3004,
            AltitudeTerrain = 3005,

            Pitot = 4000,
            IndicatedAirspeed = 4001,
            TrueAirspeed = 4002,

            Rangefinder = 5000,

            Navigator = 6000,
            TargetBearing = 6001,
            TrackError = 6002,
            AirspeedError = 6003,
            AltitudeError = 6004,

            FlightControl = 7000,
            DesiredPitch = 7001,
            DesiredRoll = 7002,
            DesiredHeading = 7003,

            PowerSystem = 8000,
            Throttle = 8001,

            Battery = 9000,

            Rssi = 10001,
            Noise = 10002,
            RemoteRssi = 10003,
            RemoteNoise = 10004,
            Errors = 10005,
            Fixed = 10006,

            Wind = 11000,

            LandingSystem = 12000,
            DeviationX = 12001,
            DeviationY = 12002,
            SizeX = 12003,
            SizeY = 12004,
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
        TelemetryMap parameters() const;

        QList<TelemetryId> changedParameterKeys() const;
        TelemetryMap takeChangedParameters();

        Telemetry* parentNode() const;
        Telemetry* childNode(TelemetryId id);
        Telemetry* childNode(const TelemetryList& path);
        QList<Telemetry*> childNodes() const;

    public slots:
        void setParameter(TelemetryId id, const QVariant& value);
        void setParameter(const TelemetryList& path, const QVariant& value);
        void notify();

    signals:
        void parametersChanged(Telemetry::TelemetryMap parameters); // Only changed parameters
        void parametersUpdated(Telemetry::TelemetryMap parameters); // All node's parameters

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
