#include "units.h"

// Qt
#include <QMap>

using namespace utils;

namespace
{
    QMap<Units::SpeedUnits, double> speedUnitCoefs =
    {
        { Units::Mps, 1.0 },
        { Units::Kph, 3.6 },
        { Units::Knots, 1.943844 },
        { Units::Mph, 2.236936 }
    };

    QMap<Units::DistanceUnits, double> distanceUnitCoefs =
    {
        { Units::Meters, 1.0 },
        { Units::Kilometers, 1000.0 },
        { Units::Feets, 0.3048 },
        { Units::Miles, 1609.344 }
    };
}

Units::Units(QObject* parent):
    QObject(parent)
{}

double Units::convertSpeedTo(SpeedUnits to, double value)
{
    if (qIsNaN(value)) return qQNaN();
    return value * ::speedUnitCoefs[to];
}

double Units::convertSpeedFrom(Units::SpeedUnits from, double value)
{
    if (qIsNaN(value)) return qQNaN();
    return value / ::speedUnitCoefs[from];
}

double Units::convertSpeed(SpeedUnits from, SpeedUnits to, double value)
{
    return Units::convertSpeedTo(to, convertSpeedFrom(from, value));
}

// distance and speed coefs are inverted(historicaly)
double Units::convertDistanceTo(DistanceUnits to, double value)
{
    if (qIsNaN(value)) return qQNaN();
    return value / ::distanceUnitCoefs[to];
}

double Units::convertDistanceFrom(Units::DistanceUnits from, double value)
{
    if (qIsNaN(value)) return qQNaN();
    return value * ::distanceUnitCoefs[from];
}

double Units::convertDistance(DistanceUnits from, DistanceUnits to, double value)
{
    return Units::convertDistanceTo(to, convertDistanceFrom(from, value));
}

QString Units::trSpeedUnits(SpeedUnits unit)
{
    switch (unit)
    {
    case Mps: return tr("m/s");
    case Kph: return tr("km/h");
    case Knots: return tr("knot");
    case Mph: return tr("mph");
    default: return QString();
    }
}

QString Units::trDistanceUnits(DistanceUnits unit)
{
    switch (unit)
    {
    case Meters: return tr("m");
    case Kilometers: return tr("km");
    case Feets: return tr("ft");
    case Miles: return tr("mi");
    default: return QString();
    }
}
