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

        Q_PROPERTY(int systemId READ systemId WRITE setSystemId
                   NOTIFY systemIdChanged)
        Q_PROPERTY(int componentId READ componentId WRITE setComponentId
                   NOTIFY componentIdChanged)

        Q_PROPERTY(bool addEnabled READ isAddEnabled NOTIFY addEnabledChanged)
        Q_PROPERTY(QList<QObject*> links READ links NOTIFY linksChanged)

        Q_PROPERTY(QStringList serialDevices READ serialDevices CONSTANT)
        Q_PROPERTY(QVariantList serialBaudRates READ serialBaudRates CONSTANT)

    public:
        ConnectionSettingsPresenter(
                domain::AbstractCommunicator* communicator, QObject* view);
        ~ConnectionSettingsPresenter() override;

        int systemId() const;
        int componentId() const;

        bool isAddEnabled() const;

        QList<QObject*> links() const;

        QStringList serialDevices() const; // TODO: service for serial devices
        QVariantList serialBaudRates() const;

    public slots:
        void setSystemId(int systemId);
        void setComponentId(int componentId);

        void addSerialLink();
        void addUdpLink();

        void removeLink(QObject* link);

    signals:
        void systemIdChanged(int systemId);
        void componentIdChanged(int componentId);

        void addEnabledChanged(bool addEnabled);
        void linksChanged();

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // CONNECTION_SETTINGS_PRESENTER_H
