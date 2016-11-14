#ifndef MAVLINK_HELPERS_H
#define MAVLINK_HELPERS_H

#include <cstdint>

namespace domain
{
    int32_t encodeLatLon(double value)
    {
        return value * 1e7;
    }

    int32_t encodeAltitude(double value)
    {
        return value * 1000;
    }

    double decodeLatLon(int32_t value)
    {
        return value / 1e7;
    }

    float decodeAltitude(double value)
    {
        return value / 1000;
    }
}

#endif // MAVLINK_HELPERS_H
