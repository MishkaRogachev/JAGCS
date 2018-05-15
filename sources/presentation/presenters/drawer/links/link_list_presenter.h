#ifndef LINK_LIST_PRESENTER_H
#define LINK_LIST_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace domain
{
    class CommunicationService;
}

namespace presentation
{
    class LinkListPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit LinkListPresenter(QObject* parent = nullptr);

    public slots:
        void updateLinks();
        void addUdpLink();
        void addSerialLink();

    private:
        domain::CommunicationService* const m_service;
    };
}

#endif // LINK_LIST_PRESENTER_H
