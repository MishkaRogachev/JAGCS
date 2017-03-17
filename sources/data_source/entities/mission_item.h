#ifndef MISSION_ITEM_H
#define MISSION_ITEM_H

// Internal
#include "base_entity.h"

namespace data_source
{
    class MissionItem: public BaseEntity
    {
        Q_OBJECT

        Q_PROPERTY(int missionId READ missionId WRITE setMissionId)
        Q_PROPERTY(int sequence READ sequence WRITE setSequence)
        Q_PROPERTY(Command command READ command WRITE setCommand)
        Q_PROPERTY(float altitude READ altitude WRITE setAltitude)
        Q_PROPERTY(bool altitudeRelative READ isAltitudeRelative WRITE setAltitudeRelative)
        Q_PROPERTY(double latitude READ latitude WRITE setLatitude)
        Q_PROPERTY(double longitude READ longitude WRITE setLongitude)
        Q_PROPERTY(float radius READ radius WRITE setRadius)
        Q_PROPERTY(float pitch READ pitch WRITE setPitch)
        Q_PROPERTY(int periods READ periods WRITE setPeriods)

    public:
        enum Command: quint8
        {
            UnknownCommand = 0,
            Home,
            Takeoff,
            Waypoint,
            LoiterAltitude,
            LoiterTurns,
            Continue,
            Return,
            Landing,
        };

        MissionItem(int id, QObject* parent = nullptr);

        static QString tableName();
        static QString insertString();
        static QString updateString();

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

        float radius() const;
        void setRadius(float radius);

        float pitch() const;
        void setPitch(float pitch);

        int periods() const;
        void setPeriods(int periods);

    private:
        int m_missionId;
        int m_sequence;
        Command m_command;
        float m_altitude;
        bool m_altitudeRelative;
        double m_latitude;
        double m_longitude;
        float m_radius;
        float m_pitch;
        int m_periods;

        Q_ENUM(Command)
    };
}

#endif // MISSION_ITEM_H
