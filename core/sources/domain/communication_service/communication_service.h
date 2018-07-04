#ifndef COMMUNICATION_SERVICE_H
#define COMMUNICATION_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "dto_traits.h"
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

        dto::LinkDescriptionPtr description(int id) const;
        dto::LinkDescriptionPtrList descriptions() const;

        dto::LinkStatisticsPtr statistics(int descriptionId) const;
        dto::LinkStatisticsPtrList statistics() const;

        void init();

    public slots:
        bool save(const dto::LinkDescriptionPtr& description);
        bool remove(const dto::LinkDescriptionPtr& description);

        void setLinkConnected(const dto::LinkDescriptionPtr& description, bool connected);

    signals:
        void descriptionAdded(dto::LinkDescriptionPtr description);
        void descriptionRemoved(dto::LinkDescriptionPtr description);
        void descriptionChanged(dto::LinkDescriptionPtr description);
        void linkStatusChanged(dto::LinkDescriptionPtr description);
        void linkStatisticsChanged(dto::LinkStatisticsPtr statistics);
        void linkSent(int linkId);
        void linkRecv(int linkId);

    private slots:
        void onLinkStatusChanged(int linkId, bool connected);
        void onLinkStatisticsChanged(int linkId,
                                     int timestamp,
                                     int bytesReceivedSec,
                                     int bytesSentSec);
        void onMavLinkStatisticsChanged(int linkId,
                                        int packetsReceived,
                                        int packetsDrops);
        void onMavlinkProtocolChanged(int linkId,
                                      dto::LinkDescription::Protocol protocol);
        void onLinkErrored(int linkId, const QString& error);
        void onDevicesChanged();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMUNICATION_SERVICE_H
