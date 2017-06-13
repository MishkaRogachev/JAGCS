#ifndef STATUSBAR_PRESENTER_H
#define STATUSBAR_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class StatusbarPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit StatusbarPresenter(QObject* parent);

    signals:
        void setMode(const QString& mode);

    protected:
        void connectView(QObject* view) override;
    };
}

#endif // STATUSBAR_PRESENTER_H
