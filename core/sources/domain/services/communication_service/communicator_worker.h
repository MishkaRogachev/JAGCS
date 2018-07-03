#ifndef COMMUNICATOR_WORKER_H
#define COMMUNICATOR_WORKER_H

#include <QObject>
#include <QMap>

// Internal
#include "link_description.h"
#include "abstract_communicator.h"

#include "i_link_factory.h"

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
        ~CommunicatorWorker() override;

    signals:
        void setCommunicator(comm::AbstractCommunicator* communicator);
        void updateLink(int linkId, const comm::LinkFactoryPtr& factory,
                        bool autoconnect);
        void removeLink(int linkId);
        void setLinkConnected(int linkId, bool connected);

        void linkStatusChanged(int linkId, bool connected);
        void linkStatisticsChanged(int linkId, int timestamp,
                                   int bytesReceivedSec, int bytesSentSec);
        void mavLinkStatisticsChanged(int linkId, int packetsReceived,
                                      int packetsDrops);
        void mavLinkProtocolChanged(int linkId,
                                    dto::LinkDescription::Protocol protocol);
        void linkSent(int linkId);
        void linkRecv(int linkId);
        void linkErrored(int linkId, QString error);

    private slots:
        void onMavLinkStatisticsChanged(comm::AbstractLink* link,
                                        int packetsReceived,
                                        int packetsDrops);
        void onMavLinkProtocolChanged(comm::AbstractLink* link,
                                      comm::AbstractCommunicator::Protocol protocol);

        void setCommunicatorImpl(comm::AbstractCommunicator* communicator);
        void updateLinkImpl(int linkId, const comm::LinkFactoryPtr& factory,
                            bool autoconnect);
        void removeLinkImpl(int linkId);
        void setLinkConnectedImpl(int linkId, bool connected);

    protected:
        void timerEvent(QTimerEvent* event) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMUNICATOR_WORKER_H
