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
        ~LogListPresenter() override;

    public slots:
        void updateLogs();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // LOG_LIST_PRESENTER_H 
