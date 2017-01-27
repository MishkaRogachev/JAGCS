#ifndef MISSION_SERVICE_H
#define MISSION_SERVICE_H

#include <QObject>

namespace domain
{
    class Mission;
    class Vehicle;

    class MissionService: public QObject
    {
        Q_OBJECT

    public:
        explicit MissionService(QObject* parent = nullptr);
        ~MissionService() override;

        const QList<Mission*>& missions() const;
        QList<Mission*> assignedMissions() const;

        Mission* missionForVehicleId(uint8_t id);

    public slots:
        void addMission(Mission* mission);
        void addNewMission();
        void addVehiclesMision(Vehicle* vehicle);
        void removeMission(Mission* mission);
        void deleteMission(Mission* mission);

        void downloadMission(Mission* mission);
        void uploadMission(Mission* mission);

    signals:
        void missionAdded(Mission* mission);
        void missionRemoved(Mission* mission);

        // TODO: remove from interface
        void requestMission(uint8_t id);
        void sendMission(uint8_t id);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSION_SERVICE_H
