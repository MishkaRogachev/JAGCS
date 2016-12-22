#include "continue_mission_item.h"

using namespace domain;

ContinueMissionItem::ContinueMissionItem(Mission* mission):
    MissionItem(mission, Continue),
    m_altitude(0)
{}

float ContinueMissionItem::altitude() const
{
    return m_altitude;
}

void ContinueMissionItem::setAltitude(float altitude)
{
    if (qFuzzyCompare(m_altitude, altitude)) return;

    m_altitude = altitude;
    emit altitudeChanged(altitude);
}
