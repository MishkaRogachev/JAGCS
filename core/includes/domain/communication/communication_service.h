#ifndef COMMUNICATION_SERVICE_H
#define COMMUNICATION_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "link_traits.h"
#include "link_description.h"

#include "i_communication_plugin.h"

namespace domain
{
    class SerialDeviceManager;

    class CommunicationService: public QObject
    {
        Q_OBJECT

    public:
        explicit CommunicationService(QObject* parent = nullptr);
        ~CommunicationService() override;

        data_source::LinkDescriptionPtr description(int id) const;
        data_source::LinkDescriptionPtrList descriptions() const;

        void addPlugin(ICommunicationPlugin* plugin);
        void removePlugin(ICommunicationPlugin* plugin);

        QStringList availableProtocols() const;

    public slots:
        bool save(const data_source::LinkDescriptionPtr& description);
        bool remove(const data_source::LinkDescriptionPtr& description);

        void setLinkConnected(int descriptionId, bool connected);

    signals:
        void availableProtocolsChanged();

        void descriptionAdded(data_source::LinkDescriptionPtr description);
        void descriptionRemoved(data_source::LinkDescriptionPtr description);
        void descriptionChanged(data_source::LinkDescriptionPtr description);
        void linkConnectedChanged(data_source::LinkDescriptionPtr description, bool connected);

    private slots:
        void onLinkConnectedChanged(int descriptionId, bool connected);
        void onLinkStatisticsChanged(int descriptionId,
                                     int timestamp,
                                     int bytesReceivedSec,
                                     int bytesSentSec);
        void onLinkErrored(int descriptionId, const QString& error);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMUNICATION_SERVICE_H
