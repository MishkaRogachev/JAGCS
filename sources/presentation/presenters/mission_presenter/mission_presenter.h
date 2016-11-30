#ifndef MISSION_PRESENTER_H
#define MISSION_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class DomainEntry;
}

namespace presentation
{
    class MissionPresenter: public BasePresenter
    {
    public:
        MissionPresenter(QObject* object);
        ~MissionPresenter() override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSIONPRESENTER_H
