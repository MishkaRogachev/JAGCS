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

    public slots:
        void updateLog();

    protected:
        void connectView(QObject* view) override;
    };
}

#endif // LOGBOOK_PRESENTER_H
