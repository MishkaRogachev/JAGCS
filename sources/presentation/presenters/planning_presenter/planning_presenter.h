#ifndef PLANNING_PRESENTER_H
#define PLANNING_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace presentation
{
    class PlanningPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit PlanningPresenter(QObject* parent = nullptr);
        ~PlanningPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // PLANNING_PRESENTER_H
