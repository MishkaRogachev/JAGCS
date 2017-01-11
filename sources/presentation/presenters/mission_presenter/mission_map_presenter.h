#ifndef MISSION_MAP_PRESENTER_H
#define MISSION_MAP_PRESENTER_H

#include "flight_map_presenter.h"

namespace domain
{
    class MissionService;
    class Mission;
}

namespace presentation
{
    class MissionMapPresenter: public FlightMapPresenter
    {
        Q_OBJECT

    public:
        explicit MissionMapPresenter(domain::MissionService* missionService,
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
