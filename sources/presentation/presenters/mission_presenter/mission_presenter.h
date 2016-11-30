#ifndef MISSION_PRESENTER_H
#define MISSION_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class VehicleService;
}

namespace presentation
{
    class MissionPresenter: public BasePresenter
    {
    public:
        MissionPresenter(domain::VehicleService* vehicleService, QObject* object);
        ~MissionPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSIONPRESENTER_H
