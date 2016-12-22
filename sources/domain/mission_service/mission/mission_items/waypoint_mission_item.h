#ifndef WAYPOINT_MISSION_ITEM_H
#define WAYPOINT_MISSION_ITEM_H

#include "position_mission_item.h"

namespace domain
{
    class WaypointMissionItem: public PositionMissionItem
    {
        Q_OBJECT

        Q_PROPERTY(float acceptanceRadius READ acceptanceRadius
                   WRITE setAcceptanceRadius NOTIFY acceptanceRadiusChanged)

    public:
        WaypointMissionItem(Mission* mission);

        float acceptanceRadius() const;

    public slots:
        void setAcceptanceRadius(float acceptanceRadius);

    signals:
        void acceptanceRadiusChanged(float acceptanceRadius);

    private:
        float m_acceptanceRadius;
    };

}

#endif // WAYPOINT_MISSION_ITEM_H
