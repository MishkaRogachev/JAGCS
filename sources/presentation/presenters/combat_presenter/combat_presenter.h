#ifndef COMBAT_PRESENTER_H
#define COMBAT_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace domain
{
    class DomainEntry;
}

namespace presentation
{
    class CombatPresenter: public BasePresenter
    {
    public:
        explicit CombatPresenter(domain::DomainEntry* entry, QObject* parent = nullptr);
        ~CombatPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMBAT_PRESENTER_H
