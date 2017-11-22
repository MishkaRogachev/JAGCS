#ifndef COMMUNICATION_LINK_PRESENTER_H
#define COMMUNICATION_LINK_PRESENTER_H

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
    class CommunicationLinkPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        CommunicationLinkPresenter(QObject* parent = nullptr);

    public slots:
        void setLink(int id);
        void updateRates();
        void updateDevices();
        void updateLink();
        void updateStatistics();
        void setConnected(bool connected);
        void save();
        void remove();

    private:
        domain::SerialPortService* const m_serialPortsService;
        domain::CommunicationService* const m_commService;
        dao::LinkDescriptionPtr m_description;
    };
}

#endif // COMMUNICATION_LINK_PRESENTER_H
