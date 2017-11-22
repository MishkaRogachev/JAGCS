#ifndef COMMUNICATIONS_PRESENTER_H
#define COMMUNICATIONS_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace domain
{
    class CommunicationService;
}

namespace presentation
{
    class CommunicationPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit CommunicationPresenter(QObject* parent = nullptr);

    public slots:
        void updateLinks();
        void addUdpLink();
        void addSerialLink();

    private:
        domain::CommunicationService* const m_service;
    };
}

#endif // COMMUNICATIONS_PRESENTER_H
