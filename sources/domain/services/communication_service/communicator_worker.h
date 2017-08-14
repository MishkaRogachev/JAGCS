#ifndef COMMUNICATOR_WORKER_H
#define COMMUNICATOR_WORKER_H

#include <QObject>
#include <QMap>

// Internal
#include "dao_traits.h"
#include "communication_traits.h"

namespace comm
{
    class AbstractCommunicator;
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
        // TODO: description change fixes
        void linkStatisticsChanged(const dao::LinkDescriptionPtr& description,
                                   int bytesReceived, int bytesSent, bool connected);
        void mavLinkStatisticsChanged(const dao::LinkDescriptionPtr& description,
                                      int packetsReceived, int packetsDrops);
        void mavLinkProtocolChanged(const dao::LinkDescriptionPtr& description,
                                    comm::Protocol protocol);

    public slots:
        void initCommunicator(comm::ICommunicatorFactory* commFactory);
        void updateLinkFromDescription(const dao::LinkDescriptionPtr& description);
        void removeLinkByDescription(const dao::LinkDescriptionPtr& description);
        void setLinkConnected(const dao::LinkDescriptionPtr& description, bool connected);

    private slots:
        void onLinkStatisticsChanged(comm::AbstractLink* link, int bytesReceived, int bytesSent);
        void onMavLinkStatisticsChanged(comm::AbstractLink* link, int packetsReceived, int packetsDrops);
        void onMavLinkProtocolChanged(comm::AbstractLink* link, comm::Protocol protocol);

    private:
        comm::AbstractCommunicator* m_communicator = nullptr;
        QMap<dao::LinkDescriptionPtr, comm::AbstractLink*> m_descriptedLinks;
    };
}

#endif // COMMUNICATOR_WORKER_H
