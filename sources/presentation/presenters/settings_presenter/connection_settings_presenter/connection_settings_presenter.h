#ifndef CONNECTION_SETTINGS_PRESENTER_H
#define CONNECTION_SETTINGS_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class AbstractCommunicator;
}

namespace presentation
{
    class ConnectionSettingsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        ConnectionSettingsPresenter(domain::AbstractCommunicator* communicator,
                                    QObject* view);
        ~ConnectionSettingsPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private slots:
        void updateSystemId(uint8_t systemId);
        void updateComponentId(uint8_t componentId);
        void updateLinks();
        void updateSerialDevices();
        void updateSerialBaudRates();

        void onSystemIdRequested(int systemId);
        void onComponentIdRequested(int componentId);
        void onRequestNewUdp();
        void onRequestNewSerial();
        void onRequestRemoveLink(QObject* link);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // CONNECTION_SETTINGS_PRESENTER_H
