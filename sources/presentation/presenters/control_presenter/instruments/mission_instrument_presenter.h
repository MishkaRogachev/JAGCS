#ifndef MISSION_INSTRUMENT_PRESENTER_H
#define MISSION_INSTRUMENT_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MissionInstrumentPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        MissionInstrumentPresenter(int vehicleId, QObject* parent = nullptr);
        ~MissionInstrumentPresenter() override;

    public slots:
        void updateWaypoints();
        void updateCurrentWaypoint();

    protected:
        void connectView(QObject* view) override;

        void setViewConnected(bool connected);

    private slots:
        void onCommandSetWaypoint(int item);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_INSTRUMENT_PRESENTER_H
