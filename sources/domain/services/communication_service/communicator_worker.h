#ifndef COMMUNICATOR_WORKER_H
#define COMMUNICATOR_WORKER_H

#include <QObject>
#include <QMap>

// Internal
#include "dao_traits.h"
#include "link_description.h"
#include "abstract_communicator.h"

namespace comm
{
    class ICommunicatorFactory;
    class AbstractLink;
}

namespace domain
{
    class CommunicatorWorker: public QObject
    {
        Q_OBJECT

    public:
        explicit CommunicatorWorker(QObject* parent = nullptr);

        comm::AbstractCommunicator* communicator() const;

    signals:
        void linkStatusChanged(int linkId, bool connected);
        void linkStatisticsChanged(int linkId, int timestamp,
                                   int bytesReceivedSec, int bytesSentSec);
        void mavLinkStatisticsChanged(int linkId, int packetsReceived,
                                      int packetsDrops);
        void mavLinkProtocolChanged(int linkId,
                                    dao::LinkDescription::Protocol protocol);

    public slots:
        void initCommunicator(comm::ICommunicatorFactory* commFactory);
        void updateLinkFromDescription(const dao::LinkDescriptionPtr& description);
        void removeLinkByDescription(const dao::LinkDescriptionPtr& description);
        void setLinkConnected(const dao::LinkDescriptionPtr& description,
                              bool connected);

    private slots:
        void onLinkStatisticsChanged(comm::AbstractLink* link, int bytesReceived,
                                     int bytesSent);
        void onMavLinkStatisticsChanged(comm::AbstractLink* link, int packetsReceived,
                                        int packetsDrops);
        void onMavLinkProtocolChanged(comm::AbstractLink* link,
                                      comm::AbstractCommunicator::Protocol protocol);

    private:
        comm::AbstractCommunicator* m_communicator = nullptr;
        QMap<int, comm::AbstractLink*> m_descriptedLinks;
    };
}

#endif // COMMUNICATOR_WORKER_H
