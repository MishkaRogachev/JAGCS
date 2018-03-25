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
        
        Q_INVOKABLE static float convertSpeedTo(SpeedUnits to, float value);
        Q_INVOKABLE static float convertSpeedFrom(SpeedUnits from, float value);
        Q_INVOKABLE static float convertSpeed(SpeedUnits from, SpeedUnits to, float value);
        Q_INVOKABLE static float convertDistanceTo(DistanceUnits to, float value);
        Q_INVOKABLE static float convertDistanceFrom(DistanceUnits from, float value);
        Q_INVOKABLE static float convertDistance(DistanceUnits from, DistanceUnits to, float value);

        Q_INVOKABLE static QString trSpeedUnits(SpeedUnits unit);
        Q_INVOKABLE static QString trDistanceUnits(DistanceUnits unit);

    private:
        Q_ENUM(SpeedUnits)
        Q_ENUM(DistanceUnits)
    };
}

#endif // UNITS_H
