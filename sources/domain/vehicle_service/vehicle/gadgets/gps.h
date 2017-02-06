#ifndef GPS_H
#define GPS_H

// Qt
#include <QGeoCoordinate>

namespace domain
{
    class Gps
    {
        Q_GADGET

        Q_PROPERTY(Fix fix READ fix CONSTANT)
        Q_PROPERTY(int satellitesVisible READ satellitesVisible CONSTANT)
        Q_PROPERTY(QGeoCoordinate coordinate READ coordinate CONSTANT)
        Q_PROPERTY(float course READ course CONSTANT)
        Q_PROPERTY(int eph READ eph CONSTANT)
        Q_PROPERTY(int epv READ epv CONSTANT)

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
            float course = 0,
            int eph = 0, int epv = 0);

        Fix fix() const;
        int satellitesVisible() const;
        QGeoCoordinate coordinate() const;
        float course() const;
        int eph() const;
        int epv() const;

        bool operator ==(const Gps& other);

    private:
        Fix m_fix;
        int m_satellitesVisible;
        QGeoCoordinate m_coordinate;
        float m_course;
        int m_eph;
        int m_epv;

        Q_ENUM(Fix)
    };
}

#endif // GPS_H
