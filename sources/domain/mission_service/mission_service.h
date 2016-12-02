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

        Mission* mission(uint8_t id) const;
        uint8_t missionId(Mission* mission) const;
        QList<Mission*> missions() const;
        QList<uint8_t> missionIds() const;

        Mission* requestMission(uint8_t id);

    public slots:
        void removeMission(uint8_t id);

    signals:
        void missionAdded(uint8_t id);
        void missionRemoved(uint8_t id);

        void commandRequestMission(uint8_t id);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSION_SERVICE_H
