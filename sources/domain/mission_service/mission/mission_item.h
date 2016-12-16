#ifndef MISSION_ITEM_H
#define MISSION_ITEM_H

#include <QObject>
#include <QGeoCoordinate>

namespace domain
{
    class Mission;

    class MissionItem: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(unsigned sequence READ sequence CONSTANT)
        Q_PROPERTY(QGeoCoordinate coordinate READ coordinate
                   WRITE setCoordinate NOTIFY coordinateChanged)
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

        MissionItem(Command command, Mission* parent);

        unsigned sequence() const;
        QGeoCoordinate coordinate() const;
        Command command() const;
        bool isCurrent() const;

    public slots:
        void setCoordinate(const QGeoCoordinate& coordinate);
        void setGlobalCoordinate(double latitude,
                                 double longitude,
                                 float altitude);
        // TODO: store relative altitude flag
        void setCoordinateRelativeAltitude(double latitude,
                                           double longitude,
                                           float altitude);

        void setCommand(Command command);
        void setCurrent(bool current);

    signals:
        void coordinateChanged(const QGeoCoordinate& coordinate);
        void commandChanged(Command command);
        void currentChanged(bool current);

    private:
        Mission* m_mission;
        QGeoCoordinate m_coordinate;
        Command m_command;
        bool m_current; // TODO: current for Vehicle

        Q_ENUM(Command)
    };
}

#endif // MISSION_ITEM_H
