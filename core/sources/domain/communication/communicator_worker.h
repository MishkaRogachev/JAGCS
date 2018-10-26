#ifndef COMMUNICATOR_WORKER_H
#define COMMUNICATOR_WORKER_H

#include <QObject>
#include <QMap>

// Internal
#include "communication_link.h"
#include "abstract_communicator.h"

#include "i_link_factory.h"

namespace data_source
{
    class AbstractLink;
    class SerialDevicePool;
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
        void addCommunicator(data_source::AbstractCommunicator* communicator);
        void deleteCommunicator(data_source::AbstractCommunicator* communicator);

        void updateLink(int linkId, const data_source::LinkFactoryPtr& factory,
                        bool autoconnect, const QString& protocol);
        void removeLink(int linkId);
        void setLinkConnected(int linkId, bool connected);

        void linkStatusChanged(int linkId, bool connected);
        void linkStatisticsChanged(int linkId, int timestamp,
                                   int bytesReceivedSec, int bytesSentSec);

        void linkSent(int linkId);
        void linkRecv(int linkId);
        void linkErrored(int linkId, QString error);

    private slots:
        void addCommunicatorImpl(data_source::AbstractCommunicator* communicator);
        void deleteCommunicatorImpl(data_source::AbstractCommunicator* communicator);

        void updateLinkImpl(int linkId, const data_source::LinkFactoryPtr& factory,
                            bool autoconnect, const QString& protocol);
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
