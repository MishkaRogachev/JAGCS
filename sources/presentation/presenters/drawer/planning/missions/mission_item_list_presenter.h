#ifndef MISSION_ITEM_LIST_PRESENTER_H
#define MISSION_ITEM_LIST_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MissionItemListPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionItemListPresenter(QObject* parent = nullptr);
        ~MissionItemListPresenter() override;

    public slots:
        void setMission(int id);

    protected:
        void connectView(QObject* view);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_ITEM_LIST_PRESENTER_H
