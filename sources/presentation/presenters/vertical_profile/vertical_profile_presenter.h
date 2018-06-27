#ifndef VERTICAL_PROFILE_PRESENTER_H
#define VERTICAL_PROFILE_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class VerticalProfilePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit VerticalProfilePresenter(QObject* parent = nullptr);

    public slots:
        void setMission(int missionId);
        void updateMission();
        void clearMission();

    private:
        domain::MissionService* m_service;
        int m_missionId = 0;
    };
}

#endif // VERTICAL_PROFILE_PRESENTER_H
