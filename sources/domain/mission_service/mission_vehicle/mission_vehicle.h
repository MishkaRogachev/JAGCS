#ifndef MISSION_VEHICLE_H
#define MISSION_VEHICLE_H

// Qt
#include <QObject>

// Internal
#include "position.h"

namespace domain
{
    class Vehicle;
    class Mission;

    class MissionVehicle: public QObject
    {
        Q_OBJECT

    public:
        explicit MissionVehicle(Mission* mission, Vehicle* vehicle);

        Mission* mission() const;
        Vehicle* vehicle() const;

    public slots:
        void setVehicle(Vehicle* vehicle);

    signals:
        void vehicleChanged(Vehicle* vehicle);

    private slots:
        void onHomePositionChanged(const Position& homePosition);

    private:
        Mission* const m_mission;
        Vehicle* m_vehicle;
    };
}

#endif // MISSION_VEHICLE_H
