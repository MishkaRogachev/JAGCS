#ifndef TAKEOFF_MISSON_ITEM_H
#define TAKEOFF_MISSON_ITEM_H

#include "direction_mission_item.h"

namespace domain
{
    class TakeoffMissionItem: public DirectionMissionItem
    {
        Q_OBJECT

        Q_PROPERTY(float pitch READ pitch WRITE setPitch NOTIFY pitchChanged)

    public:
        explicit TakeoffMissionItem(Mission* mission);

        float pitch() const;

    public slots:
        void setPitch(float pitch);

    signals:
        void pitchChanged(float pitch);

    private:
        float m_pitch;
    };
}

#endif // TAKEOFFMISSONITEM_H
