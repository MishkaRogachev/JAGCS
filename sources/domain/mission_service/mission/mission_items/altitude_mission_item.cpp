#include "altitude_mission_item.h"

using namespace domain;

AltitudeMissionItem::AltitudeMissionItem(Mission* mission, Command command,
                                         bool relativeAltitude):
    MissionItem(mission, command),
    m_altitude(0),
    m_relativeAltitude(relativeAltitude)
{}

float AltitudeMissionItem::altitude() const
{
    return m_altitude;
}

bool AltitudeMissionItem::isRelativeAltitude() const
{
    return m_relativeAltitude;
}

void AltitudeMissionItem::clone(MissionItem* mission)
{
    auto altitudeItem = qobject_cast<AltitudeMissionItem*>(mission);

    if (altitudeItem)
    {
        this->setAltitude(altitudeItem->altitude());
        this->setRelativeAltitude(altitudeItem->isRelativeAltitude());
    }

    MissionItem::clone(mission);
}

void AltitudeMissionItem::setAltitude(float altitude)
{
    if (qFuzzyCompare(m_altitude, altitude)) return;

    m_altitude = altitude;
    emit altitudeChanged(altitude);
}

void AltitudeMissionItem::setRelativeAltitude(bool relativeAltitude)
{
    if (m_relativeAltitude == relativeAltitude) return;

    m_relativeAltitude = relativeAltitude;
    emit relativeAltitudeChanged(relativeAltitude);
}
