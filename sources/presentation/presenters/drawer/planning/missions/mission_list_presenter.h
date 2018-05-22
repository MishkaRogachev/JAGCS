#ifndef MISSION_LIST_PRESENTER_H
#define MISSION_LIST_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MissionListPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionListPresenter(QObject* parent = nullptr);
        ~MissionListPresenter() override;

    public slots:
        void addMission();

    protected:
        void connectView(QObject* view);

    private:
         class Impl;
         QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_LIST_PRESENTER_H
