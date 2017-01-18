#include "altitude_mission_item.h"

// Internal
#include "mission.h"

using namespace domain;

AltitudeMissionItem::AltitudeMissionItem(Mission* mission, Command command,
                                         bool relativeAltitude):
    MissionItem(mission, command),
    m_altitude(0),
    m_relativeAltitude(relativeAltitude)
{
    this->setAltitude(-1 * this->altitudeChange());
}

float AltitudeMissionItem::altitude() const
{
    return m_altitude;
}

bool AltitudeMissionItem::isRelativeAltitude() const
{
    return m_relativeAltitude;
}

float AltitudeMissionItem::altitudeChange() const
{
    const uint8_t seq = this->sequence();
    if (seq < 1) return 0;

    AltitudeMissionItem* previous = nullptr;
    for (uint8_t prevSeq = seq - 1; prevSeq > 0 ; prevSeq--)
    {
        previous = qobject_cast<AltitudeMissionItem*>(
                       this->mission()->item(prevSeq));
        if (!previous) continue;

        if (this->isRelativeAltitude() == previous->isRelativeAltitude())
        {
            return this->altitude() - previous->altitude();
        }
        else return 0; // FIXME: relative altitude
    }
    return 0;
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
