#ifndef MISSION_ITEM_PRESENTER_H
#define MISSION_ITEM_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace db
{
    class DbFacade;
}

namespace presentation
{
    class MissionItemPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionItemPresenter(db::DbFacade* dbFacade, QObject* object = nullptr);
        ~MissionItemPresenter() override;

        db::MissionPtr selectedMission() const;

    public slots:
        void setMission(const db::MissionPtr& mission);
        void setMissionItem(const db::MissionItemPtr& item);

    protected:
        void connectView(QObject* view) override;

    private slots:
        void updateCount(bool gotoNewItem = false);
        void updateItem();

        void onAddItem();
        void onRemoveItem();
        void onSelectItem(int index);

        void onSetCommand(int command);
        void onSetAltitude(qreal altitude);
        void onSetAltitudeRelative(bool relative);
        void onSetLatitude(qreal latitude);
        void onSetLongitude(qreal longitude);
        void onSetRadius(qreal radius);
        void onSetPeriods(int periods);
        void onSetPitch(qreal pitch);

    private:
         class Impl;
         QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_ITEM_PRESENTER_H
