#ifndef LINK_LIST_PRESENTER_H
#define LINK_LIST_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace presentation
{
    class LinkListPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit LinkListPresenter(QObject* parent = nullptr);
        ~LinkListPresenter() override;

    public slots:
        void addSerialLink();
        void addUdpLink();
        void addTcpLink();
        void addBluetoothLink();

        void filter(const QString& filterString);

    protected:
        void connectView(QObject* view) override;

    private:
         class Impl;
         QScopedPointer<Impl> const d;
    };
}

#endif // LINK_LIST_PRESENTER_H
