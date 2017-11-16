#ifndef PLANNING_PRESENTER_H
#define PLANNING_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class PlanningPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit PlanningPresenter(QObject* parent = nullptr);

    protected:
        void connectView(QObject* view) override;
    };
}

#endif // PLANNING_PRESENTER_H
