#ifndef GPS_H
#define GPS_H

// Qt
#include <QGeoCoordinate>

namespace domain
{
    class Gps
    {
        Q_GADGET

    public:
        enum Fix
        {
            NoGps,
            NoFix,
            Fix2D,
            Fix3D
        };

        Gps(Fix fix = NoGps,
            const QGeoCoordinate& coordinate = QGeoCoordinate());

        Fix fix() const;
        QGeoCoordinate coordinate() const;

        bool operator ==(const Gps& other);

    private:
        Fix m_fix;
        QGeoCoordinate m_coordinate;

        Q_ENUM(Fix)
    };
}

#endif // GPS_H
