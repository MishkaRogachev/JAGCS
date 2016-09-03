#ifndef CONNECTION_PRESENTER_H
#define CONNECTION_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class ConnectionPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit ConnectionPresenter(QObject* view);
        ~ConnectionPresenter() override;

    public slots:
        void addSerialLink();
        void addUdpLink();

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // CONNECTION_PRESENTER_H
