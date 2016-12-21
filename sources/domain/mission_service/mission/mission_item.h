#ifndef MISSION_ITEM_H
#define MISSION_ITEM_H

#include <QObject>

namespace domain
{
    class Mission;

    class MissionItem: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(unsigned sequence READ sequence CONSTANT)
        Q_PROPERTY(Mission* mission READ mission CONSTANT)

        Q_PROPERTY(Command command READ command WRITE setCommand
                   NOTIFY commandChanged)

        Q_PROPERTY(double latitude READ latitude
                   WRITE setLatitude NOTIFY latitudeChanged)
        Q_PROPERTY(double longitude READ longitude
                   WRITE setLongitude NOTIFY longitudeChanged)
        Q_PROPERTY(float altitude READ altitude
                   WRITE setAltitude NOTIFY altitudeChanged)
        Q_PROPERTY(bool relativeAltitude READ isRelativeAltitude
                   WRITE setRelativeAltitude NOTIFY relativeAltitudeChanged)
        Q_PROPERTY(float pitch READ pitch WRITE setPitch NOTIFY pitchChanged)
        Q_PROPERTY(float yaw READ yaw WRITE setYaw NOTIFY yawChanged)
        Q_PROPERTY(float radius READ radius WRITE setRadius NOTIFY radiusChanged)

        Q_PROPERTY(bool hasPosition READ hasPosition NOTIFY commandChanged)
        Q_PROPERTY(bool current READ isCurrent WRITE setCurrent
                   NOTIFY currentChanged)

    public:
        enum Command
        {
            UnknownCommand = 0,
            Home,
            Takeoff,
            Waypoint,
            Loiter,
            Continue,
            Return,
            Landing
        };

        MissionItem(Command command, Mission* mission);

        Mission* mission() const;
        unsigned sequence() const;

        Command command() const;

        double latitude() const;
        double longitude() const;
        float altitude() const;
        bool isRelativeAltitude() const;
        float yaw() const;
        float pitch() const;
        float radius() const;

        bool hasPosition() const;

        bool isCurrent() const;

    public slots:
        void setCommand(Command command);

        void setLatitude(double latitude);
        void setLongitude(double longitude);
        void setAltitude(float altitude);
        void setRelativeAltitude(bool relativeAltitude);
        void setYaw(float yaw);
        void setPitch(float pitch);
        void setRadius(float radius);

        void invalidatePosition();

        void setCurrent(bool current);

    signals:
        void commandChanged(Command command);

        void latitudeChanged(double latitude);
        void longitudeChanged(double longitude);
        void altitudeChanged(float altitude);
        void relativeAltitudeChanged(bool relativeAltitude);
        void yawChanged(float yaw);
        void pitchChanged(float pitch);
        void radiusChanged(float radius);

        void currentChanged(bool current);

    private:
        Mission* const m_mission;
        Command m_command;
        double m_latitude;
        double m_longitude;
        float m_altitude;
        bool m_relativeAltitude;
        float m_pitch;
        float m_yaw;
        float m_radius;
        bool m_current; // TODO: current for Vehicle

        Q_ENUM(Command)
    };
}

#endif // MISSION_ITEM_H
