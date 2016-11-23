#ifndef MAVLINK_PROTOCOL_HELPERS_H
#define MAVLINK_PROTOCOL_HELPERS_H

#include <cstdint>

namespace domain
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

    inline double decodeLatLon(int32_t value)
    {
        return value / 1e7;
    }

    inline float decodeAltitude(double value)
    {
        return value / 1000;
    }

    inline float decodeVoltage(uint16_t value)
    {
        return value / 1000;
    }

    inline float decodeCurrent(int16_t value)
    {
        return value / 10000;
    }
}

#endif // MAVLINK_PROTOCOL_HELPERS_H
