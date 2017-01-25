#ifndef MISSION_SERVICE_H
#define MISSION_SERVICE_H

#include <QObject>

namespace domain
{
    class Mission;

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

        void assignMission(Mission* mission, uint8_t vehicleId);
        void unassignMission(Mission* mission);

        void onVehicleAdded(uint8_t vehicleId);

        void downloadMission(Mission* mission);
        void uploadMission(Mission* mission);

        void setCurrentCount(int currentCount);
        void setTotalCount(int totalCount);

    signals:
        void missionAdded(Mission* mission);
        void missionRemoved(Mission* mission);

        void currentCountChanged(int currentCount);
        void totalCountChanged(int totalCount);

        // TODO: remove from interface
        void requestMission(uint8_t id);
        void sendMission(uint8_t id);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSION_SERVICE_H
