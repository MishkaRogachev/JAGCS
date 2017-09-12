#ifndef MISSION_INSTRUMENT_PRESENTER_H
#define MISSION_INSTRUMENT_PRESENTER_H

#include "base_instrument_presenter.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MissionInstrumentPresenter: public BaseInstrumentPresenter
    {
        Q_OBJECT

    public:
        MissionInstrumentPresenter(int vehicleId, QObject* parent = nullptr);
        ~MissionInstrumentPresenter() override;

    public slots:
        void updateWaypoints();
        void updateCurrentWaypoint();
        void onDownloadMission();
        void onCancelSyncMission();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onCommandSetWaypoint(int item);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_INSTRUMENT_PRESENTER_H
