#ifndef LOGBOOK_PRESENTER_H
#define LOGBOOK_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class LogbookPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit LogbookPresenter(QObject* parent = nullptr);
        ~LogbookPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // LOGBOOK_PRESENTER_H
