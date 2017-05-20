#include "availables.h"

using namespace domain;

Availables::Availables(bool ahrsAvailable, bool insAvailable,
                       bool snsAvailable, bool compasAvailable,
                       bool airSpeedAvailable, bool barometerAvailable,
                       bool rangeFinderAvailable):
    m_ahrsAvailable(ahrsAvailable),
    m_insAvailable(insAvailable),
    m_snsAvailable(snsAvailable),
    m_compasAvailable(compasAvailable),
    m_airSpeedAvailable(airSpeedAvailable),
    m_barometerAvailable(barometerAvailable),
    m_rangeFinderAvailable(rangeFinderAvailable)
{}

bool Availables::ahrsAvailable() const
{
    return m_ahrsAvailable;
}

bool Availables::insAvailable() const
{
    return m_insAvailable;
}

bool Availables::snsAvailable() const
{
    return m_snsAvailable;
}

bool Availables::compasAvailable() const
{
    return m_compasAvailable;
}

bool Availables::airSpeedAvailable() const
{
    return m_airSpeedAvailable;
}

bool Availables::barometerAvailable() const
{
    return m_barometerAvailable;
}

bool Availables::rangeFinderAvailable() const
{
    return m_rangeFinderAvailable;
}

bool Availables::operator ==(const Availables& other)
{
    return m_ahrsAvailable == other.ahrsAvailable() &&
            m_insAvailable == other.insAvailable() &&
            m_snsAvailable == other.snsAvailable() &&
            m_compasAvailable == other.compasAvailable() &&
            m_airSpeedAvailable == other.airSpeedAvailable() &&
            m_barometerAvailable == other.barometerAvailable() &&
            m_rangeFinderAvailable == other.rangeFinderAvailable();
}
