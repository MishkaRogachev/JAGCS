#ifndef MISSION_PRESENTER_H
#define MISSION_PRESENTER_H

// Internal
#include "base_presenter.h"

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

        void rename(const QString& name);
        void setMissionVisible(bool visible);
        void remove();

    protected:
        void connectView(QObject* view);

    private:
        domain::MissionService* const m_service;
        int m_missionId;
    };
}

#endif // MISSION_PRESENTER_H
