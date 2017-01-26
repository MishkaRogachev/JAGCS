#ifndef MISSION_MAP_PRESENTER_H
#define MISSION_MAP_PRESENTER_H

#include "map_presenter.h"

namespace domain
{
    class MissionService;
    class Mission;
    class VehicleService;
}

namespace presentation
{
    class MissionMapPresenter: public MapPresenter
    {
        Q_OBJECT

    public:
        MissionMapPresenter(domain::MissionService* missionService,
                            domain::VehicleService* vehicleService,
                            QObject* parent = nullptr);
        ~MissionMapPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onMissionAdded(domain::Mission* mission);
        void onMissionRemoved(domain::Mission* mission);

        void onMissionItemsChanged();

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSION_MAP_PRESENTER_H
