#ifndef UNIFIED_PRESENTER_H
#define UNIFIED_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class UnifiedPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit UnifiedPresenter(QObject* parent = nullptr);
        ~UnifiedPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // UNIFIED_PRESENTER_H
