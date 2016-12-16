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

        Q_PROPERTY(double latitude READ latitude
                   WRITE setLatitude NOTIFY latitudeChanged)
        Q_PROPERTY(double longitude READ longitude
                   WRITE setLongitude NOTIFY longitudeChanged)
        Q_PROPERTY(float altitude READ altitude
                   WRITE setAltitude NOTIFY altitudeChanged)
        Q_PROPERTY(bool relativeAltitude READ isRelativeAltitude
                   WRITE setRelativeAltitude NOTIFY relativeAltitudeChanged)

        Q_PROPERTY(Command command READ command WRITE setCommand
                   NOTIFY commandChanged)
        Q_PROPERTY(bool current READ isCurrent WRITE setCurrent
                   NOTIFY currentChanged)

    public:
        enum Command // TODO: other commands
        {
            UnknownCommand = 0,
            Takeoff,
            Waypoint,
            Loiter,
            Return,
            Landing
        };

        MissionItem(Command command, Mission* mission);

        Mission* mission() const;
        unsigned sequence() const;

        double latitude() const;
        double longitude() const;
        float altitude() const;
        bool isRelativeAltitude() const;

        Command command() const;
        bool isCurrent() const;

    public slots:
        void setLatitude(double latitude);
        void setLongitude(double longitude);
        void setAltitude(float altitude);
        void setRelativeAltitude(bool relativeAltitude);

        void invalidatePosition();

        void setCommand(Command command);
        void setCurrent(bool current);

    signals:
        void latitudeChanged(double latitude);
        void longitudeChanged(double longitude);
        void altitudeChanged(float altitude);
        void relativeAltitudeChanged(bool relativeAltitude);
        void commandChanged(Command command);
        void currentChanged(bool current);

    private:
        Mission* const m_mission;
        double m_latitude;
        double m_longitude;
        float m_altitude;
        bool m_relativeAltitude;
        Command m_command;
        bool m_current; // TODO: current for Vehicle

        Q_ENUM(Command)
    };
}

#endif // MISSION_ITEM_H
