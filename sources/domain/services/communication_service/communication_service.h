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

        dao::LinkDescriptionPtr description(int id) const;
        dao::LinkDescriptionPtrList descriptions();

        void init();

    public slots:
        bool save(const dao::LinkDescriptionPtr& description);
        bool remove(const dao::LinkDescriptionPtr& description);

        void setLinkConnected(const dao::LinkDescriptionPtr& description, bool connected);

    signals:
        void descriptionAdded(dao::LinkDescriptionPtr description);
        void descriptionRemoved(dao::LinkDescriptionPtr description);
        void descriptionChanged(dao::LinkDescriptionPtr description);
        void linkStatusChanged(dao::LinkDescriptionPtr description);
        void linkStatisticsChanged(dao::LinkStatisticsPtr statistics);

    private slots:
        void onLinkStatusChanged(int linkId,
                                 bool connected);
        void onLinkStatisticsChanged(int linkId,
                                     int timestamp,
                                     int bytesReceivedSec,
                                     int bytesSentSec);
        void onMavLinkStatisticsChanged(int linkId,
                                        int packetsReceived,
                                        int packetsDrops);
        void onMavlinkProtocolChanged(int linkId,
                                      dao::LinkDescription::Protocol protocol);
        void onDevicesChanged();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMUNICATION_SERVICE_H
