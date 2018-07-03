#ifndef CONNECTION_PRESENTER_H
#define CONNECTION_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace presentation
{
    class ConnectionPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit ConnectionPresenter(QObject* parent = nullptr);
        ~ConnectionPresenter() override;

    public slots:
        void updateStatus();
        void updateStatistics();

        void setConnected(bool connected);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // CONNECTION_PRESENTER_H
