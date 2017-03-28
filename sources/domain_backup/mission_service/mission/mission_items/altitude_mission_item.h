#ifndef ALTITUDE_MISSION_ITEM_H
#define ALTITUDE_MISSION_ITEM_H

#include "abstract_mission_item.h"

namespace domain
{
    class AltitudeMissionItem: public AbstractMissionItem
    {
        Q_OBJECT

        Q_PROPERTY(float altitude READ altitude
                   WRITE setAltitude NOTIFY altitudeChanged)
        Q_PROPERTY(bool relativeAltitude READ isRelativeAltitude
                   WRITE setRelativeAltitude NOTIFY relativeAltitudeChanged)

    public:
        explicit AltitudeMissionItem(Mission* mission, Command command,
                                     bool relativeAltitude);

        float altitude() const;
        bool isRelativeAltitude() const;

        Q_INVOKABLE float homeAltitude() const;
        Q_INVOKABLE float absoluteAltitude() const;

        Q_INVOKABLE float climb() const;

        void clone(AbstractMissionItem* mission) override;

    public slots:
        void setAltitude(float altitude);
        void setRelativeAltitude(bool relativeAltitude);

    signals:
        void altitudeChanged(float altitude);
        void relativeAltitudeChanged(bool relativeAltitude);

    private:
        float m_altitude;
        bool m_relativeAltitude;
    };
}

#endif // ALTITUDE_MISSION_ITEM_H
