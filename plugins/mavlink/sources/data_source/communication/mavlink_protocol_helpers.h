#ifndef MAVLINK_PROTOCOL_HELPERS_H
#define MAVLINK_PROTOCOL_HELPERS_H

// Qt
#include <QGeoCoordinate>

#ifndef UINT16_MAX
// Std
#include <limits.h>

#define UINT16_MAX std::numeric_limits<std::uint16_t>::max()
#endif

namespace data_source
{
    int32_t inline hzToUs(float frequency)
    {
        return 1000000 / frequency;
    }

    inline int32_t encodeLatLon(double value)
    {
        return value * 1e7;
    }

    inline int32_t encodeAltitude(double value)
    {
        return value * 1000;
    }

    inline int16_t decodeTemperature(float value)
    {
        return value * 100;
    }

    inline uint16_t encodeCourse(float value)
    {
        return value * 100;
    }

    inline uint16_t encodeGroundSpeed(float value)
    {
        return value * 100;
    }

    inline double decodeLatLon(int32_t value)
    {
        return double(value) / 1e7;
    }

    inline float decodeAltitude(int32_t value)
    {
        return float(value) / 1000;
    }

    inline float decodeTemperature(int16_t value)
    {
        return float(value) / 100;
    }

    inline float decodeCourse(uint16_t value)
    {
        return value == UINT16_MAX ? qQNaN() : float(value) / 100;
    }

    inline float decodeGroundSpeed(uint16_t value)
    {
        return value == UINT16_MAX ? qQNaN() : float(value) / 100;
    }

    inline float getTrueAirspeed(float indicatedAirspeed, float altitude)
    {
        return indicatedAirspeed + (indicatedAirspeed * 0.02 * altitude / 1000);
    }

    inline float fixAirspeedError(float aspdError)
    {
        // APM ISSUE: https://github.com/ArduPilot/ardupilot/issues/335
        return aspdError * 0.01;
    }

    inline float fromCentidegrees(float centidegrees)
    {
        return centidegrees / 100;
    }

    inline float decodeVoltage(uint16_t value)
    {
        return float(value) / 1000;
    }

    inline float decodeCurrent(int16_t value)
    {
        return float(value) / 100;
    }

    inline QGeoCoordinate decodeCoordinate(int32_t lat, int32_t lon, int32_t alt)
    {
        if (lat == 0 && lon == 0) return QGeoCoordinate();

        return QGeoCoordinate(decodeLatLon(lat), decodeLatLon(lon), decodeAltitude(alt));
    }

    inline float decodeRssi(uint16_t value)
    {
        return qMin(qMax(qRound(value / 1.9 - 127.0), - 120), 0);
    }
}

#endif // MAVLINK_PROTOCOL_HELPERS_H
