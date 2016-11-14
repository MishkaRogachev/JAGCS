#ifndef POSITION_H
#define POSITION_H

// Qt
#include <QGeoCoordinate>
#include <QVector3D>

namespace domain
{
    class Position
    {
        Q_GADGET

        Q_PROPERTY(QGeoCoordinate coordinate READ coordinate CONSTANT)
        Q_PROPERTY(QVector3D vector READ vector CONSTANT)

    public:
        Position(const QGeoCoordinate& coordinate = QGeoCoordinate(),
                 const QVector3D& vector = QVector3D(0.0, 0.0, 0.0));

        const QGeoCoordinate& coordinate() const;
        const QVector3D& vector() const;

        bool operator ==(const Position& other);

    private:
        QGeoCoordinate m_coordinate;
        QVector3D m_vector;
    };
}

#endif // POSITION_H
