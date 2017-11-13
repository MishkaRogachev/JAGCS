#ifndef TOPBAR_PRESENTER_H
#define TOPBAR_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class TopbarPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit TopbarPresenter(QObject* parent = nullptr);
        ~TopbarPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // TOPBAR_PRESENTER_H
