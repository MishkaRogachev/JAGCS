#ifndef STATUSBAR_PRESENTER_H
#define STATUSBAR_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class StatusbarPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit StatusbarPresenter(QObject* parent = nullptr);
        ~StatusbarPresenter() override;

    signals:
        void setMode(const QString& mode);

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // STATUSBAR_PRESENTER_H
