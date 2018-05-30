#ifndef LINK_PRESENTER_H
#define LINK_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dto_traits.h"

namespace domain
{
    class CommunicationService;
}

namespace presentation
{
    class LinkPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit LinkPresenter(QObject* parent = nullptr);

    public slots:
        virtual void setLink(int id);
        virtual void updateLink();
        void updateStatus();
        void setConnected(bool connected);
        void remove();

    protected slots:
        virtual void updateStatistics(const dto::LinkStatisticsPtr& statistics);

    protected:
        domain::CommunicationService* const m_service;
        dto::LinkDescriptionPtr m_link;
    };
}

#endif // LINK_PRESENTER_H
