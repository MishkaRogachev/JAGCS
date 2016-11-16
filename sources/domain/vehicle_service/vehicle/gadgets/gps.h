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
            short satellitesVisible = -1,
            const QGeoCoordinate& coordinate = QGeoCoordinate(),
            int eph = 0, int epv = 0);

        Fix fix() const;
        int satellitesVisible() const;
        QGeoCoordinate coordinate() const;
        int eph() const;
        int epv() const;

        bool operator ==(const Gps& other);

    private:
        Fix m_fix;
        int m_satellitesVisible;
        QGeoCoordinate m_coordinate;
        int m_eph;
        int m_epv;

        Q_ENUM(Fix)
    };
}

#endif // GPS_H
