#ifndef MISSION_MAP_PRESENTER_H
#define MISSION_MAP_PRESENTER_H

#include "map_presenter.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MissionMapPresenter: public MapPresenter
    {
        Q_OBJECT

    public:
        explicit MissionMapPresenter(domain::MissionService* missionService,
                                     QObject* parent = nullptr);
        ~MissionMapPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSION_MAP_PRESENTER_H
