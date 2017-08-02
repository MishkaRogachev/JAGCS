#ifndef MISSION_ITEM_H
#define MISSION_ITEM_H

// Internal
#include "base_dao.h"

namespace dao
{
    class MissionItem: public BaseDao
    {
        Q_GADGET

        Q_PROPERTY(int missionId READ missionId WRITE setMissionId)
        Q_PROPERTY(int sequence READ sequence WRITE setSequence)
        Q_PROPERTY(Command command READ command WRITE setCommand)
        Q_PROPERTY(float altitude READ altitude WRITE setAltitude)
        Q_PROPERTY(float abortAltitude READ abortAltitude WRITE setAbortAltitude)
        Q_PROPERTY(bool altitudeRelative READ isAltitudeRelative WRITE setAltitudeRelative)
        Q_PROPERTY(double latitude READ latitude WRITE setLatitude)
        Q_PROPERTY(double longitude READ longitude WRITE setLongitude)
        Q_PROPERTY(float distance READ distance WRITE setDistance)
        Q_PROPERTY(float speed READ speed WRITE setSpeed)
        Q_PROPERTY(float radius READ radius WRITE setRadius)
        Q_PROPERTY(float pitch READ pitch WRITE setPitch)
        Q_PROPERTY(float roll READ roll WRITE setRoll)
        Q_PROPERTY(float yaw READ yaw WRITE setYaw)
        Q_PROPERTY(int repeats READ repeats WRITE setRepeats)
        Q_PROPERTY(float delay READ delay WRITE setDelay)
        Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)

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
            ChangeSpeed,

            JumpTo,

            SetServo,
            SetRelay,
            RepeatServo,
            RepeatRelay,

            SetRoi,
            MountControl,
            SetCameraTriggerDistance,
            CameraControl

            //TODO: condirion commands
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

        float abortAltitude() const;
        void setAbortAltitude(float abortAltitude);

        bool isAltitudeRelative() const;
        void setAltitudeRelative(bool altitudeRelative);

        double latitude() const;
        void setLatitude(double latitude);

        double longitude() const;
        void setLongitude(double longitude);

        float distance() const;
        void setDistance(float distance);

        float speed() const;
        void setSpeed(float speed);

        float radius() const;
        void setRadius(float radius);

        float pitch() const;
        void setPitch(float pitch);

        float roll() const;
        void setRoll(float roll);

        float yaw() const;
        void setYaw(float yaw);

        int repeats() const;
        void setRepeats(int repeats);

        int delay() const;
        void setDelay(int delay);

        bool isEnabled() const;
        void setEnabled(bool enabled);

        Status status() const;
        void setStatus(Status status);

        bool isReached() const;
        void setReached(bool reached);

        bool isCurrent() const;
        void setCurrent(bool current);

    private:
        int m_missionId = 0;
        int m_sequence = -1;
        Command m_command = UnknownCommand;
        float m_altitude = qQNaN();
        float m_abortAltitude = qQNaN();
        bool m_altitudeRelative = false;
        double m_latitude = qQNaN();
        double m_longitude = qQNaN();
        float m_distance = qQNaN();
        float m_speed = qQNaN();
        float m_radius = qQNaN();
        float m_pitch = qQNaN();
        float m_roll = qQNaN();
        float m_yaw = qQNaN();
        int m_repeats = 0;
        float m_delay = 0.0;
        bool m_enabled = false;

        Status m_status = NotActual;
        bool m_reached = false;
        bool m_current = false;

        Q_ENUM(Command)
        Q_ENUM(Status)
    };
}
#endif // MISSION_ITEM_H
