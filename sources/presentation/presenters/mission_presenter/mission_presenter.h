#ifndef MISSION_PRESENTER_H
#define MISSION_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class VehicleService;
    class MissionService;
}

namespace presentation
{
    class MissionPresenter: public BasePresenter
    {
    public:
        MissionPresenter(domain::VehicleService* vehicleService,
                         domain::MissionService* missionService,
                         QObject* object);
        ~MissionPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSIONPRESENTER_H
