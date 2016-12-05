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

    private slots:
        void onMissionAdded(uint8_t id);
        void onMissionRemoved(uint8_t id);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSION_MAP_PRESENTER_H
