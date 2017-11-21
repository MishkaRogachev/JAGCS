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
        CommunicationLinkPresenter(const dao::LinkDescriptionPtr& description,
                                   QObject* parent = nullptr);

    public slots:
        void updateRates();
        void updateDevices();
        void updateView();
        void updateStatistics();
        void setConnected(bool connected);
        void save();
        void remove();

    private:
        domain::SerialPortService* m_serialPortsService;
        domain::CommunicationService* m_commService;
        dao::LinkDescriptionPtr m_description;
    };
}

#endif // COMMUNICATION_LINK_PRESENTER_H
