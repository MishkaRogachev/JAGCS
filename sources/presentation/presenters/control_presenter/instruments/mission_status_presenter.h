#ifndef MISSION_STATUS_PRESENTER_H
#define MISSION_STATUS_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MissionStatusPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        MissionStatusPresenter(int vehicleId, QObject* parent = nullptr);
        ~MissionStatusPresenter() override;

    public slots:
        void updateWaypoints();
        void updateCurrentWaypoint();

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_STATUS_PRESENTER_H
