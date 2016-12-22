#ifndef DIRECTION_MISSON_ITEM_H
#define DIRECTION_MISSON_ITEM_H

#include "position_mission_item.h"

namespace domain
{
    class DirectionMissionItem: public PositionMissionItem
    {
        Q_OBJECT

        Q_PROPERTY(float yaw READ yaw WRITE setYaw NOTIFY yawChanged)

    public:
        DirectionMissionItem(Mission* mission, Command command,
                             bool relativeAltitude);

        float yaw() const;

    public slots:
        void setYaw(float yaw);

    signals:
        void yawChanged(float yaw);

    private:
        float m_yaw;
    };
}

#endif // DIRECTION_MISSON_ITEM_H
