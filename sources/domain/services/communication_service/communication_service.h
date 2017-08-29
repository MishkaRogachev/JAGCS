#ifndef COMMUNICATION_SERVICE_H
#define COMMUNICATION_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "dao_traits.h"
#include "link_description.h"

namespace comm
{
    class ICommunicatorFactory;
}

namespace domain
{
    class SerialPortService;

    class CommunicationService: public QObject
    {
        Q_OBJECT

    public:
        CommunicationService(SerialPortService* serialPortService, QObject* parent = nullptr);
        ~CommunicationService() override;

        dao::LinkDescriptionPtr description(int id, bool reload = false);
        dao::LinkDescriptionPtrList descriptions(const QString& condition = QString(),
                                                 bool reload  = false);

        void init();

    public slots:
        bool save(const dao::LinkDescriptionPtr& description);
        bool remove(const dao::LinkDescriptionPtr& description);

        void setLinkConnected(const dao::LinkDescriptionPtr& description, bool connected);

    signals:
        void descriptionAdded(dao::LinkDescriptionPtr description);
        void descriptionRemoved(dao::LinkDescriptionPtr description);
        void descriptionChanged(dao::LinkDescriptionPtr description);
        void linkStatisticsChanged(dao::LinkDescriptionPtr description);

    private slots:
        void onLinkStatisticsChanged(const dao::LinkDescriptionPtr& description,
                                     int bytesReceivedSec, int bytesSentSec, bool connected);
        void onMavLinkStatisticsChanged(const dao::LinkDescriptionPtr& description,
                                        int packetsReceived, int packetsDrops);
        void onMavlinkProtocolChanged(const dao::LinkDescriptionPtr& description,
                                      dao::LinkDescription::Protocol protocol);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMUNICATION_SERVICE_H
