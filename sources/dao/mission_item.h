#ifndef MISSION_ITEM_H
#define MISSION_ITEM_H

// Internal
#include "base_dao.h"

// Qt
#include <QVariant>
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
        Q_PROPERTY(QString parameters READ parameters WRITE setParameters)

    public:
        enum Command: quint8
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
            CameraControl

            //TODO: condition commands
        };

        enum Parameter: quint8
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

        enum Status: quint8
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

        Status status() const;
        void setStatus(Status status);

        bool isReached() const;
        void setReached(bool reached);

        QString parameters() const;
        void setParameters(const QString& parameters);
        QVariant parameter(Parameter key, const QVariant& parameter = QVariant());
        void setParameter(Parameter key, const QVariant& parameter);

    private:
        int m_missionId = 0;
        int m_sequence = -1;
        Command m_command = UnknownCommand;
        float m_altitude = qQNaN();
        bool m_altitudeRelative = false;
        double m_latitude = qQNaN();
        double m_longitude = qQNaN();
        QMap<Parameter, QVariant> m_parameters;

        Status m_status = NotActual;
        bool m_reached = false;

        Q_ENUM(Command)
        Q_ENUM(Parameter)
        Q_ENUM(Status)
    };
}
#endif // MISSION_ITEM_H
