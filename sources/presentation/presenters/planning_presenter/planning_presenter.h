#ifndef PLANNING_PRESENTER_H
#define PLANNING_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace domain
{
    class DomainEntry;
}

namespace presentation
{
    class PlanningPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit PlanningPresenter(domain::DomainEntry* entry, QObject* parent = nullptr);
        ~PlanningPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // PLANNING_PRESENTER_H
