#include "altitude_mission_item.h"

// Qt
#include <QDebug>

// Internal
#include "mission.h"

using namespace domain;

AltitudeMissionItem::AltitudeMissionItem(Mission* mission, Command command,
                                         bool relativeAltitude):
    AbstractMissionItem(mission, command),
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

float AltitudeMissionItem::homeAltitude() const
{
    AltitudeMissionItem* home = qobject_cast<AltitudeMissionItem*>(
                   this->mission()->item(0));
    if (!home) return 0;

    return home->altitude();
}

float AltitudeMissionItem::absoluteAltitude() const
{
    if (m_relativeAltitude)
        return this->homeAltitude() + this->altitude();

    return this->altitude();
}

float AltitudeMissionItem::climb() const
{
    if (this->sequence() < 1) return 0;

    AltitudeMissionItem* previous = nullptr;
    for (uint8_t seq = this->sequence() - 1; seq >= 0 ; seq--)
    {
        previous = qobject_cast<AltitudeMissionItem*>(
                       this->mission()->item(seq));
        if (!previous) continue;

        return this->absoluteAltitude() - previous->absoluteAltitude();
    }
    return 0;
}

void AltitudeMissionItem::clone(AbstractMissionItem* mission)
{
    auto altitudeItem = qobject_cast<AltitudeMissionItem*>(mission);

    if (altitudeItem)
    {
        this->setAltitude(altitudeItem->altitude());
        this->setRelativeAltitude(altitudeItem->isRelativeAltitude());
    }
}

void AltitudeMissionItem::setAltitude(float altitude)
{
    if (qFuzzyCompare(m_altitude, altitude)) return;

    m_altitude = altitude;
    emit altitudeChanged(altitude);
    emit dataChanged();
}

void AltitudeMissionItem::setRelativeAltitude(bool relativeAltitude)
{
    if (m_relativeAltitude == relativeAltitude) return;

    m_relativeAltitude = relativeAltitude;
    emit relativeAltitudeChanged(relativeAltitude);
    emit dataChanged();
}
