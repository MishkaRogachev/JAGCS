#ifndef COMMUNICATIONS_PRESENTER_H
#define COMMUNICATIONS_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace presentation
{
    class CommunicationPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit CommunicationPresenter(QObject* parent = nullptr);
        ~CommunicationPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onLinkAdded(const dao::LinkDescriptionPtr& description);
        void onLinkChanged(const dao::LinkDescriptionPtr& description);
        void onLinkStatisticsChanged(const dao::LinkDescriptionPtr& description);
        void onLinkRemoved(const dao::LinkDescriptionPtr& description);
        void updateCommunicationsLinks();

        void onAddUdpLink();
        void onAddSerialLink();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMUNICATIONS_PRESENTER_H
