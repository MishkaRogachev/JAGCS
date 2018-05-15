#ifndef LOG_LIST_PRESENTER_H
#define LOG_LIST_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class LogListPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit LogListPresenter(QObject* parent = nullptr);

    public slots:
        void updateLog();

    protected:
        void connectView(QObject* view) override;
    };
}

#endif // LOG_LIST_PRESENTER_H
