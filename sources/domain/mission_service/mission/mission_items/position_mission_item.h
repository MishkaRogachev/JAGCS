#ifndef POSITION_MISSION_ITEM_H
#define POSITION_MISSION_ITEM_H

#include "altitude_mission_item.h"

namespace domain
{
    class PositionMissionItem: public AltitudeMissionItem
    {
        Q_OBJECT

        Q_PROPERTY(double latitude READ latitude
                   WRITE setLatitude NOTIFY latitudeChanged)
        Q_PROPERTY(double longitude READ longitude
                   WRITE setLongitude NOTIFY longitudeChanged)

    public:
        PositionMissionItem(Mission* mission, Command command,
                            bool relativeAltitude);

        double latitude() const;
        double longitude() const;

        Q_INVOKABLE float azimuth() const;

        void clone(MissionItem* mission) override;

    public slots:
        void setLatitude(double latitude);
        void setLongitude(double longitude);

    signals:
        void latitudeChanged(double latitude);
        void longitudeChanged(double longitude);

    private:
        double m_latitude;
        double m_longitude;
    };
}

#endif // POSITION_MISSION_ITEM_H
