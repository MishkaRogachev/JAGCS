#ifndef LINK_PRESENTER_H
#define LINK_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace domain
{
    class SerialPortService;
    class CommunicationService;
}

namespace presentation
{
    class LinkPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        LinkPresenter(QObject* parent = nullptr);
        ~LinkPresenter() override;

    public slots:
        void setLink(int id);
        void updateRates();
        void updateDevices();
        void updateLink();
        void updateStatus();
        void setConnected(bool connected);
        void save();
        void remove();

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // LINK_PRESENTER_H
