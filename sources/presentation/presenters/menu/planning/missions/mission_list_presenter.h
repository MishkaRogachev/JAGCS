#ifndef MISSION_LIST_PRESENTER_H
#define MISSION_LIST_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MissionListPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionListPresenter(QObject* parent = nullptr);

    public slots:
        void updateMissions();
        void addMission();

    private:
        domain::MissionService* const m_service;
    };
}

#endif // MISSION_LIST_PRESENTER_H
