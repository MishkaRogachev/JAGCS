#ifndef COMMUNICATOR_WORKER_H
#define COMMUNICATOR_WORKER_H

#include <QObject>
#include <QMap>

// Internal
#include "dao_traits.h"

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
        void linkStatisticsChanged(const dao::LinkDescriptionPtr& description,
                                   int bytesReceivedSec,
                                   int bytesSentSec,
                                   bool connected);

    public slots:
        void initCommunicator(comm::ICommunicatorFactory* commFactory);
        void updateLinkFromDescription(const dao::LinkDescriptionPtr& description);
        void removeLinkByDescription(const dao::LinkDescriptionPtr& description);
        void setLinkConnected(const dao::LinkDescriptionPtr& description, bool connected);

    private slots:
        void onLinkStatisticsChanged();

    private:
        comm::AbstractCommunicator* m_communicator = nullptr;
        QMap<dao::LinkDescriptionPtr, comm::AbstractLink*> m_descriptedLinks;
    };
}

#endif // COMMUNICATOR_WORKER_H
