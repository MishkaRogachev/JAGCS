#ifndef MISSION_STATUS_PRESENTER_H
#define MISSION_STATUS_PRESENTER_H

#include "base_presenter.h"

namespace db
{
    class DbFacade;
}

namespace presentation
{
    class MissionStatusPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        MissionStatusPresenter(db::DbFacade* facade, int vehicleId,
                               QObject* parent = nullptr);
        ~MissionStatusPresenter() override;

    public slots:
        void updateView();

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_STATUS_PRESENTER_H
