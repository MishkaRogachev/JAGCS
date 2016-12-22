#ifndef LOITER_MISSION_ITEM_H
#define LOITER_MISSION_ITEM_H

#include "position_mission_item.h"

namespace domain
{
    class LoiterMissionItem: public PositionMissionItem
    {
        Q_OBJECT

        Q_PROPERTY(float radius READ radius WRITE setRadius
                   NOTIFY radiusChanged)

    public:
        explicit LoiterMissionItem(Mission* mission);

        float radius() const;

    public slots:
        void setRadius(float radius);

    signals:
        void radiusChanged(float radius);

    private:
        float m_radius;
    };
}

#endif // LOITER_MISSION_ITEM_H
