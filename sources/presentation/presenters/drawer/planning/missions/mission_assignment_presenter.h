#ifndef MISSION_ASSIGNMENT_PRESENTER_H
#define MISSION_ASSIGNMENT_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MissionAssignmentPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionAssignmentPresenter(QObject* parent = nullptr);

    public slots:
        void setMission(int id);

        void updateAssignment();

        void assignVehicle(int vehicleId);
        void uploadMission();
        void downloadMission();
        void cancelSyncMission();

    protected:
        void connectView(QObject* view);

    protected:
        domain::MissionService* const m_service;
        int m_missionId;
    };
}

#endif // MISSION_ASSIGNMENT_PRESENTER_H
