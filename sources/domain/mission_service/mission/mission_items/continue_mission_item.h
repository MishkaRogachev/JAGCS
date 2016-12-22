#ifndef CONTINUE_MISSION_ITEM_H
#define CONTINUE_MISSION_ITEM_H

#include "mission_item.h"

namespace domain
{
    class ContinueMissionItem: public MissionItem
    {
        Q_OBJECT

        Q_PROPERTY(float altitude READ altitude
                   WRITE setAltitude NOTIFY altitudeChanged)

    public:
        explicit ContinueMissionItem(Mission* mission);

        float altitude() const;

    public slots:
        void setAltitude(float altitude);

    signals:
        void altitudeChanged(float altitude);

    private:
        float m_altitude;
    };
}

#endif // CONTINUE_MISSION_ITEM_H
