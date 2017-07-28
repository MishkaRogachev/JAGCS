#ifndef COMMUNICATION_SETTINGS_PRESENTER_H
#define COMMUNICATION_SETTINGS_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace presentation
{
    class CommunicationSettingsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit CommunicationSettingsPresenter(QObject* parent = nullptr);
        ~CommunicationSettingsPresenter() override;

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

#endif // COMMUNICATION_SETTINGS_PRESENTER_H
