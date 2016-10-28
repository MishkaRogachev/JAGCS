#ifndef MAP_ITEM_H
#define MAP_ITEM_H

// Qt
#include <QGeoCoordinate>
#include <QUrl>

namespace presentation
{
    class MapItem
    {
    public:
        MapItem(const QGeoCoordinate& position = QGeoCoordinate(),
                int direction = 0,
                const QUrl& mark = QUrl("qrc:/indicators/unknown_mark.svg"));

        QGeoCoordinate position() const;
        int direction() const;
        QUrl mark() const;

    private:
        QGeoCoordinate m_position;
        int m_direction;
        QUrl m_mark;
    };
}

#endif // MAP_ITEM_H
