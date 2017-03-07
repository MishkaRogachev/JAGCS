#ifndef MISSION_SERVICE_H
#define MISSION_SERVICE_H

#include <QObject>

namespace domain
{
    class Mission;
    class AbstractMissionItem;
    class AbstractVehicle;

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
        void addVehiclesMision(domain::AbstractVehicle* vehicle);
        void removeMission(Mission* mission);
        void deleteMission(Mission* mission);

        void downloadMission(Mission* mission);
        void uploadMission(Mission* mission);

    signals:
        void missionAdded(Mission* mission);
        void missionRemoved(Mission* mission);

        void missionAssigned(Mission* mission);
        void missionUnassigned(Mission* mission);

        // TODO: remove from interface
        void requestMission(uint8_t id);
        void requestMissionItem(uint8_t id, uint16_t seq);
        void sendMission(uint8_t id);
        void sendMissionItem(uint8_t id, uint16_t seq);

    private slots:
        void onMissionAssigned();
        void onMissionUnassigned();
        void onMissionItemDataChanged(AbstractMissionItem* item);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSION_SERVICE_H
