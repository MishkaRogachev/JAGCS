#ifndef COMMUNICATION_LINK_PRESENTER_H
#define COMMUNICATION_LINK_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace db
{
    class DbFacade;
}

namespace domain
{
    class CommunicationService;
}

namespace presentation
{
    class CommunicationLinkPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        CommunicationLinkPresenter(db::DbFacade* dbFacade,
                                   domain::CommunicationService* service,
                                   const db::LinkDescriptionPtr& description,
                                   QObject* parent = nullptr);

        db::LinkDescriptionPtr description() const;

    public slots:
        void updateView();
        void updateStatistics();
        void setConnected(bool connected);
        void save();
        void remove();

    protected:
        void connectView(QObject* view) override;

    private:
        db::DbFacade* m_dbFacade;
        domain::CommunicationService* m_service;
        db::LinkDescriptionPtr m_description;
    };
}

#endif // COMMUNICATION_LINK_PRESENTER_H
