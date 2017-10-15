#ifndef MISSION_INSTRUMENT_PRESENTER_H
#define MISSION_INSTRUMENT_PRESENTER_H

#include "base_instrument_presenter.h"
#include "dao_traits.h"

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
        void onDownloadMission();
        void onCancelSyncMission();

        void selectMissionItem(const dao::MissionItemPtr& item);
        void goToItem();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onSelectItem(int item);

    signals:
        void missionItemSelected(const dao::MissionItemPtr& item);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_INSTRUMENT_PRESENTER_H
