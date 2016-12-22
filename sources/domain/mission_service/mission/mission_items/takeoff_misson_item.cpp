#include "takeoff_misson_item.h"

using namespace domain;

TakeoffMissonItem::TakeoffMissonItem(Mission* mission):
    DirectionMissonItem(mission, Takeoff, true),
    m_pitch(15)
{}

float TakeoffMissonItem::pitch() const
{
    return m_pitch;
}

void TakeoffMissonItem::setPitch(float pitch)
{
    if (qFuzzyCompare(m_pitch, pitch)) return;

    m_pitch = pitch;
    emit pitchChanged(pitch);
}
