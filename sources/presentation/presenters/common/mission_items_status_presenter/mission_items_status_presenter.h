#ifndef MISSION_ITEMS_STATUS_PRESENTER_H
#define MISSION_ITEMS_STATUS_PRESENTER_H

#include "base_presenter.h"
#include "dao_traits.h"

namespace presentation
{
    class MissionItemsStatusPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionItemsStatusPresenter(QObject* object = nullptr);
        ~MissionItemsStatusPresenter() override;

    public slots:
        void selectMission(const dao::MissionPtr& mission);
        void selectMissionItem(const dao::MissionItemPtr& item);

    protected:
        void connectView(QObject* view) override;

    private slots:
        void updateItemsStatus();
        void updateSelectedItem();

    signals:
        void selectItem(int index);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_ITEMS_STATUS_PRESENTER_H
