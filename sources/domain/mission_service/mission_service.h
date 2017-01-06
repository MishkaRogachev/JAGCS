#ifndef MISSION_SERVICE_H
#define MISSION_SERVICE_H

#include <QObject>

namespace domain
{
    class Mission;

    // TODO: Mission uuid separated from vehicle Id
    class MissionService: public QObject
    {
        Q_OBJECT

    public:
        explicit MissionService(QObject* parent = nullptr);
        ~MissionService() override;

        Mission* missionForVehicle(uint8_t vehicleId) const;
        uint8_t vehicleForMission(Mission* mission) const;

        const QList<Mission*>& missions() const;

        Mission* requestMissionForVehicle(uint8_t vehicleId);

        int currentCount() const; // TODO: VehicleMission
        int totalCount() const;

    public slots:
        void addNewMission();
        void removeMission(Mission* mission);
        void deleteMission(Mission* mission);

        void setVehicleForMission(uint8_t vehicleId, Mission* mission) const;

        void setCurrentCount(int currentCount);
        void setTotalCount(int totalCount);

    signals:
        void missionAdded(Mission* mission);
        void missionRemoved(Mission* mission);

        void currentCountChanged(int currentCount);
        void totalCountChanged(int totalCount);

        void commandDownloadMission(uint8_t vehicleId);
        void commandUploadMission(uint8_t vehicleId);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSION_SERVICE_H
