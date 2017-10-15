#ifndef MISSION_ITEM_H
#define MISSION_ITEM_H

// Internal
#include "base_dao.h"

// Qt
#include <QVariant>
#include <QGeoCoordinate>
#include <QMap>

namespace dao
{
    class MissionItem: public BaseDao
    {
        Q_GADGET

        Q_PROPERTY(int missionId READ missionId WRITE setMissionId)
        Q_PROPERTY(int sequence READ sequence WRITE setSequence)
        Q_PROPERTY(Command command READ command WRITE setCommand)
        Q_PROPERTY(float altitude READ altitude WRITE setAltitude)
        Q_PROPERTY(bool altitudeRelative READ isAltitudeRelative WRITE setAltitudeRelative)
        Q_PROPERTY(double latitude READ latitude WRITE setLatitude)
        Q_PROPERTY(double longitude READ longitude WRITE setLongitude)
        // TODO: replace parameters with command arguments
        Q_PROPERTY(QString parameters READ parameters WRITE setParameters)
        Q_PROPERTY(Status status READ status WRITE setStatus)
        Q_PROPERTY(bool current READ isCurrent WRITE setCurrent)
        Q_PROPERTY(bool reached READ isReached WRITE setReached)

    public:
        enum Command
        {
            UnknownCommand = 0,

            Home,
            Takeoff,
            Waypoint,
            LoiterUnlim,
            LoiterAltitude,
            LoiterTurns,
            LoiterTime,
            Continue,
            Return,
            Landing,

            SetSpeed,

            JumpTo,

            SetServo,
            SetRelay,
            RepeatServo,
            RepeatRelay,

            SetRoi,
            MountControl,
            SetCameraTriggerDistance,
            CameraControl,

            //TODO: condition commands

            TargetPoint
        };

        enum Parameter
        {
            UnknownParameter = 0,

            AbortAltitude,
            Pitch,
            Roll,
            Yaw,
            Distance,
            Speed,
            IsGroundSpeed,
            Throttle,
            Radius,
            HeadingRequired,
            Clockwise,
            Repeats,
            Time,
            Enabled
        };

        enum Status
        {
            NotActual = 0,
            Downloading,
            Uploading,
            Actual
        };

        int missionId() const;
        void setMissionId(int missionId);

        int sequence() const;
        void setSequence(int sequence);

        Command command() const;
        void setCommand(Command command);

        float altitude() const;
        void setAltitude(float altitude);

        bool isAltitudeRelative() const;
        void setAltitudeRelative(bool altitudeRelative);

        double latitude() const;
        void setLatitude(double latitude);

        double longitude() const;
        void setLongitude(double longitude);

        QGeoCoordinate coordinate() const;
        void setCoordinate(const QGeoCoordinate& coordinate);

        QString parameters() const;
        void setParameters(const QString& parameters);
        QVariant parameter(Parameter key, const QVariant& parameter = QVariant());
        void setParameter(Parameter key, const QVariant& parameter);
        void clearParameters();
        void clearSuperfluousParameters();

        bool isAltitudedItem() const;
        bool isPositionatedItem() const;

        Status status() const;
        void setStatus(Status status);

        bool isCurrent() const;
        void setCurrent(bool current);

        bool isReached() const;
        void setReached(bool reached);

    private:
        int m_missionId = 0;
        int m_sequence = -1;
        Command m_command = UnknownCommand;
        QGeoCoordinate m_coordinate;
        float m_altitude = 0;
        bool m_altitudeRelative = false;
        QMap<Parameter, QVariant> m_parameters;
        Status m_status = NotActual;
        bool m_current = false;
        bool m_reached = false;

        Q_ENUM(Command)
        Q_ENUM(Parameter)
        Q_ENUM(Status)
    };
}
#endif // MISSION_ITEM_H
