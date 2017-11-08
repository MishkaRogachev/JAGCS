#ifndef MENU_PRESENTER_H
#define MENU_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class MenuPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MenuPresenter(QObject* parent = nullptr);
        ~MenuPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MENU_PRESENTER_H
