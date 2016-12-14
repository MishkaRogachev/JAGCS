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

        Mission* missionForVehicle(uint8_t id) const;
        uint8_t vehicleForMission(Mission* mission) const;

        const QList<Mission*>& missions() const;

        Mission* requestMissionForVehicle(uint8_t id);

    public slots:
        void addNewMission();
        void removeMission(Mission* mission);
        void deleteMission(Mission* mission);

    signals:
        void missionAdded(Mission* mission);
        void missionRemoved(Mission* mission);

        void commandRequestMission(uint8_t id);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSION_SERVICE_H
