#ifndef MISSION_PRESENTER_H
#define MISSION_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MissionPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionPresenter(QObject* parent = nullptr);

    public slots:
        void setMission(int id);
        void updateMission();
        void updateAssignment();

        void rename(const QString& name);
        void setMissionVisible(bool visible);
        void remove();
        void assignVehicle(int id);
        void uploadMission();
        void downloadMission();
        void cancelSyncMission();

    private:
        domain::MissionService* const m_service;
        dao::MissionPtr m_mission;
    };
}

#endif // MISSION_PRESENTER_H
