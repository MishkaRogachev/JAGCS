#ifndef COMMUNICATION_SERVICE_H
#define COMMUNICATION_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "communication_link.h"
#include "i_communication_plugin.h"

namespace domain
{
    class CommunicationService: public QObject
    {
        Q_OBJECT

    public:
        explicit CommunicationService(QObject* parent = nullptr);
        ~CommunicationService() override;

        QList<LinkDescription*> descriptions() const;

        void addPlugin(ICommunicationPlugin* plugin);
        void removePlugin(ICommunicationPlugin* plugin);

        QStringList availableProtocols() const;

    public slots:
        bool save(LinkDescription* description);
        bool remove(LinkDescription* description);

        void setLinkConnected(int descriptionId, bool connected);

    signals:
        void availableProtocolsChanged();

        void linkAdded(LinkDescription* description);
        void linkRemoved(LinkDescription* description);

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
