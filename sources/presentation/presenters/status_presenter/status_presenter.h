#ifndef STATUS_PRESENTER_H
#define STATUS_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class StatusPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit StatusPresenter(QObject* view);

    public slots:
        void quit();
    };
}

#endif // STATUS_PRESENTER_H
