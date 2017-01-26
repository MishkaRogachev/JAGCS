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
        explicit MissionVehicle(Mission* mission, Vehicle* vehicle = nullptr);
        ~MissionVehicle() override;

        Mission* mission() const;
        Vehicle* vehicle() const;
        uint8_t vehicleId() const;

        int currentProgress() const;
        int totalProgress() const;

    public slots:
        void setVehicle(Vehicle* vehicle);

        void setCurrentProgress(int currentProgress);
        void setTotalProgress(int totalProgress);

    signals:
        void vehicleChanged(Vehicle* vehicle);

        void currentProgressChanged(int currentProgress);
        void totalProgressChanged(int totalProgress);

    private slots:
        void onHomePositionChanged(const Position& homePosition);

    private:
        Mission* const m_mission;
        Vehicle* m_vehicle;

        int m_currentProgress;
        int m_totalProgress;
    };
}

#endif // MISSION_VEHICLE_H
