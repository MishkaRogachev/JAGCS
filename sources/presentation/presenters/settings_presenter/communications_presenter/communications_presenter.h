#ifndef COMMUNICATIONS_PRESENTER_H
#define COMMUNICATIONS_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace domain
{
    class CommunicationManager;
}

namespace presentation
{
    class CommunicationsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        CommunicationsPresenter(domain::CommunicationManager* manager,
                                QObject* parent);
        ~CommunicationsPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onLinkAdded(const db::LinkDescriptionPtr& description);
        void onLinkRemoved(const db::LinkDescriptionPtr& description);
        void updateCommunicationsLinks();

        void onAddUdpLink();
        void onAddSerialLink();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMUNICATIONS_PRESENTER_H
