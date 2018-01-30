#include "communicator_worker.h"

// Qt
#include <QTime>
#include <QThread>
#include <QDebug>

// Internal
#include "link_description.h"

#include "abstract_communicator.h"
#include "abstract_link.h"

namespace
{
    dao::LinkDescription::Protocol toDaoProtocol(comm::AbstractCommunicator::Protocol protocol)
    {
        switch (protocol) {
        case comm::AbstractCommunicator::MavLink1: return dao::LinkDescription::MavLink1;
        case comm::AbstractCommunicator::MavLink2: return dao::LinkDescription::MavLink2;
        default:
        case comm::AbstractCommunicator::Unknown: return dao::LinkDescription::UnknownProtocol;
        }
    }
}

using namespace comm;
using namespace domain;

class CommunicatorWorker::Impl
{
public:
    comm::AbstractCommunicator* communicator = nullptr;
    QMap<int, comm::AbstractLink*> descriptedLinks;
};

CommunicatorWorker::CommunicatorWorker(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    connect(this, &CommunicatorWorker::setCommunicator,
            this, &CommunicatorWorker::setCommunicatorImpl);
    connect(this, &CommunicatorWorker::updateLink,
            this, &CommunicatorWorker::updateLinkImpl);
    connect(this, &CommunicatorWorker::removeLink,
            this, &CommunicatorWorker::removeLinkImpl);
    connect(this, &CommunicatorWorker::setLinkConnected,
            this, &CommunicatorWorker::setLinkConnectedImpl);
}

CommunicatorWorker::~CommunicatorWorker()
{}

void CommunicatorWorker::onLinkStatisticsChanged(AbstractLink* link,
                                                 int bytesReceived,
                                                 int bytesSent)
{
    int linkId = d->descriptedLinks.key(link, 0);
    if (!linkId) return;

    emit linkStatisticsChanged(linkId,
                               QTime::currentTime().msecsSinceStartOfDay(),
                               bytesReceived, bytesSent);
}

void CommunicatorWorker::onMavLinkStatisticsChanged(AbstractLink* link,
                                                    int packetsReceived,
                                                    int packetsDrops)
{
    int linkId = d->descriptedLinks.key(link, 0);
    if (!linkId) return;

    emit mavLinkStatisticsChanged(linkId, packetsReceived, packetsDrops);
}

void CommunicatorWorker::onMavLinkProtocolChanged(AbstractLink* link,
                                                  AbstractCommunicator::Protocol protocol)
{
    int linkId = d->descriptedLinks.key(link, 0);
    if (!linkId) return;

    emit mavLinkProtocolChanged(linkId, ::toDaoProtocol(protocol));
}

void CommunicatorWorker::setCommunicatorImpl(AbstractCommunicator* communicator)
{
    // TODO: if several communicators, who owns the link?
    if (d->communicator)
    {
        for (AbstractLink* link: d->descriptedLinks.values())
        {
            d->communicator->removeLink(link);
        }

        disconnect(d->communicator, 0, this, 0);

        delete d->communicator;
    }

    d->communicator = communicator;

    if (d->communicator)
    {
        d->communicator->setParent(this);

        connect(d->communicator, &AbstractCommunicator::linkStatisticsChanged,
                this, &CommunicatorWorker::onLinkStatisticsChanged);
        connect(d->communicator, &AbstractCommunicator::mavLinkStatisticsChanged,
                this, &CommunicatorWorker::onMavLinkStatisticsChanged);
        connect(d->communicator, &AbstractCommunicator::mavLinkProtocolChanged,
                this, &CommunicatorWorker::onMavLinkProtocolChanged);

        for (AbstractLink* link: d->descriptedLinks.values())
        {
            d->communicator->addLink(link);
        }
    }
}

void CommunicatorWorker::updateLinkImpl(int linkId,
                                        const LinkFactoryPtr& factory,
                                        bool autoconnect)
{
    AbstractLink* link = nullptr;

    if (d->descriptedLinks.contains(linkId))
    {
        link = d->descriptedLinks[linkId];
        factory->update(link);
    }
    else
    {
        link = factory->create();
        if (!link) return;

        link->setParent(this);

        d->descriptedLinks[linkId] = link;
        if (d->communicator) d->communicator->addLink(link);

        if (autoconnect)
        {
            link->connectLink();
            emit linkStatusChanged(linkId, link->isConnected());
        }
    }
}

void CommunicatorWorker::removeLinkImpl(int linkId)
{
    if (d->descriptedLinks.contains(linkId))
    {
        AbstractLink* link = d->descriptedLinks.take(linkId);

        if (d->communicator) d->communicator->removeLink(link);
        delete link;
    }
}

void CommunicatorWorker::setLinkConnectedImpl(int linkId, bool connected)
{
    AbstractLink* link = d->descriptedLinks[linkId];
    if (!link) return;

    link->setConnected(connected);
    emit linkStatusChanged(linkId, link->isConnected());
}

