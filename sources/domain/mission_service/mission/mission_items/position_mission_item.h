#ifndef POSITION_MISSION_ITEM_H
#define POSITION_MISSION_ITEM_H

#include "mission_item.h"

namespace domain
{
    class PositionMissionItem: public MissionItem
    {
        Q_OBJECT

        Q_PROPERTY(double latitude READ latitude
                   WRITE setLatitude NOTIFY latitudeChanged)
        Q_PROPERTY(double longitude READ longitude
                   WRITE setLongitude NOTIFY longitudeChanged)
        Q_PROPERTY(float altitude READ altitude
                   WRITE setAltitude NOTIFY altitudeChanged)
        Q_PROPERTY(bool relativeAltitude READ isRelativeAltitude
                   WRITE setRelativeAltitude NOTIFY relativeAltitudeChanged)

    public:
        PositionMissionItem(Mission* mission, Command command,
                            bool relativeAltitude);

        double latitude() const;
        double longitude() const;
        float altitude() const;
        bool isRelativeAltitude() const;

    public slots:
        void setLatitude(double latitude);
        void setLongitude(double longitude);
        void setAltitude(float altitude);
        void setRelativeAltitude(bool relativeAltitude);

    signals:
        void latitudeChanged(double latitude);
        void longitudeChanged(double longitude);
        void altitudeChanged(float altitude);
        void relativeAltitudeChanged(bool relativeAltitude);

    private:
        double m_latitude;
        double m_longitude;
        float m_altitude;
        bool m_relativeAltitude;
    };
}

#endif // POSITION_MISSION_ITEM_H
