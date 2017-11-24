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
        domain::SerialPortService* const m_serialService;
        domain::CommunicationService* const m_commService;
        dao::LinkDescriptionPtr m_description;
    };
}

#endif // LINK_PRESENTER_H
