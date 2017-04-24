#ifndef COMMUNICATIONS_PRESENTER_H
#define COMMUNICATIONS_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace domain
{
    class CommunicationService;
}

namespace presentation
{
    class CommunicationsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit CommunicationsPresenter(domain::CommunicationService* service,
                                         QObject* parent = nullptr);
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
