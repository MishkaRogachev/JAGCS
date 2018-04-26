#ifndef UNITS_H
#define UNITS_H

#include <QObject>

namespace utils
{
    class Units: public QObject
    {
        Q_OBJECT
        
    public:
        explicit Units(QObject* parent = nullptr);

        enum SpeedUnits
        {
            Mps = 0,        // Meters per second, default
            Kph,            // Kilometers per hour
            Knots,          // Knots
            Mph             // Miles per hour
        };

        enum DistanceUnits
        {
            Meters = 0,     // Default
            Kilometers,
            Miles,
            Feets
        };
        
        Q_INVOKABLE static double convertSpeedTo(SpeedUnits to, double value);
        Q_INVOKABLE static double convertSpeedFrom(SpeedUnits from, double value);
        Q_INVOKABLE static double convertSpeed(SpeedUnits from, SpeedUnits to, double value);
        Q_INVOKABLE static double convertDistanceTo(DistanceUnits to, double value);
        Q_INVOKABLE static double convertDistanceFrom(DistanceUnits from, double value);
        Q_INVOKABLE static double convertDistance(DistanceUnits from, DistanceUnits to,
                                                  double value);

        Q_INVOKABLE static QString trSpeedUnits(SpeedUnits unit);
        Q_INVOKABLE static QString trDistanceUnits(DistanceUnits unit);

    private:
        Q_ENUM(SpeedUnits)
        Q_ENUM(DistanceUnits)
    };
}

#endif // UNITS_H
