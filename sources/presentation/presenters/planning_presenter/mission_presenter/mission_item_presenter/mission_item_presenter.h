#ifndef MISSION_ITEM_PRESENTER_H
#define MISSION_ITEM_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MissionItemPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionItemPresenter(domain::MissionService* service, QObject* object = nullptr);
        ~MissionItemPresenter() override;

        dao::MissionPtr selectedMission() const;

    public slots:
        void setMission(const dao::MissionPtr& mission);
        void setMissionItem(const dao::MissionItemPtr& item);

        void remove();
        void selectItem(int index);
        void save();
        void updateView();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void updateCount(bool gotoNewItem = false);

    private:
         class Impl;
         QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_ITEM_PRESENTER_H
