#include "satellite_info.h"

using namespace dto;

SatelliteInfo::SatelliteInfo(quint8 prn, bool used, quint8 elevation, quint8 azimuth, quint8 snr):
    m_prn(prn),
    m_used(used),
    m_elevation(elevation),
    m_azimuth(azimuth),
    m_snr(snr)
{}

quint8 SatelliteInfo::prn() const
{
    return m_prn;
}

bool SatelliteInfo::used() const
{
    return m_used;
}

quint8 SatelliteInfo::elevation() const
{
    return m_elevation;
}

quint8 SatelliteInfo::azimuth() const
{
    return m_azimuth;
}

quint8 SatelliteInfo::snr() const
{
    return m_snr;
}

void SatelliteInfo::setPrn(quint8 prn)
{
    m_prn = prn;
}

void SatelliteInfo::setUsed(bool used)
{
    m_used = used;
}

void SatelliteInfo::setElevation(quint8 elevation)
{
    m_elevation = elevation;
}

void SatelliteInfo::setAzimuth(quint8 azimuth)
{
    m_azimuth = azimuth;
}

void SatelliteInfo::setSnr(quint8 snr)
{
    m_snr = snr;
}
