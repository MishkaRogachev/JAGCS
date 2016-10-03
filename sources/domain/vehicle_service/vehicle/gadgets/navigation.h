#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QGeoCoordinate>
#include <QVector3D>

namespace domain
{
    class Navigation
    {
        Q_GADGET

        Q_PROPERTY(QGeoCoordinate position READ position CONSTANT)
        Q_PROPERTY(QVector3D groundSpeed READ groundSpeed CONSTANT)

    public:
        Navigation(const QGeoCoordinate& position = QGeoCoordinate(),
                   const QVector3D& groundSpeed = QVector3D(0.0, 0.0, 0.0));

        QGeoCoordinate position() const;
        QVector3D groundSpeed() const;

    private:
        QGeoCoordinate m_position;
        QVector3D m_groundSpeed;
    };
}

#endif // NAVIGATION_H
