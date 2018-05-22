#ifndef MISSION_ITEM_LIST_PRESENTER_H
#define MISSION_ITEM_LIST_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MissionItemListPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionItemListPresenter(QObject* parent = nullptr);

    public slots:
        void setMission(int id);
        void updateMissionItems();

    protected:
        void connectView(QObject* view);

    private:
        domain::MissionService* const m_service;
        int m_missionId;
    };
}

#endif // MISSION_ITEM_LIST_PRESENTER_H
