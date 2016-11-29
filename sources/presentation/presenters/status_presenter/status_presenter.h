#ifndef STATUS_PRESENTER_H
#define STATUS_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class StatusPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit StatusPresenter(QObject* parent);

    signals:
        void setMode(const QString& mode);

    protected:
        void connectView(QObject* view) override;
    };
}

#endif // STATUS_PRESENTER_H
