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

    public:
        MissionItem(Mission* parent);

        QGeoCoordinate coordinate() const;
        bool isCurrent() const;
        unsigned sequence() const;

    public slots:
        void setCoordinate(const QGeoCoordinate& coordinate);
        void setCurrent(bool current);

    signals:
        void coordinateChanged(const QGeoCoordinate& coordinate);
        void currentChanged(bool current);

    private:
        Mission* m_mission;
        QGeoCoordinate m_coordinate;
        bool m_current;
    };
}

#endif // MISSION_ITEM_H
