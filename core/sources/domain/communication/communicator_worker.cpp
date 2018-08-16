#include "communicator_worker.h"

// Qt
#include <QTimerEvent>
#include <QTime>
#include <QThread>
#include <QDebug>

// Internal
#include "link_description.h"

#include "abstract_communicator.h"
#include "abstract_link.h"

namespace
{
    const int second = 1000;
}

using namespace data_source;
using namespace domain;

class CommunicatorWorker::Impl
{
public:
    QMap<int, data_source::AbstractLink*> descriptedLinks;
    QMap<int, QString> descriptedProtocols;
    QList<data_source::AbstractCommunicator*> communicators;

    int statisticsTimer = 0;
};

CommunicatorWorker::CommunicatorWorker(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    connect(this, &CommunicatorWorker::addCommunicator,
            this, &CommunicatorWorker::addCommunicatorImpl);
    connect(this, &CommunicatorWorker::deleteCommunicator,
            this, &CommunicatorWorker::deleteCommunicatorImpl);
    connect(this, &CommunicatorWorker::updateLink,
            this, &CommunicatorWorker::updateLinkImpl);
    connect(this, &CommunicatorWorker::removeLink,
            this, &CommunicatorWorker::removeLinkImpl);
    connect(this, &CommunicatorWorker::setLinkConnected,
            this, &CommunicatorWorker::setLinkConnectedImpl);

    d->statisticsTimer = this->startTimer(::second);
}

CommunicatorWorker::~CommunicatorWorker()
{}

void CommunicatorWorker::addCommunicatorImpl(AbstractCommunicator* communicator)
{
    if (d->communicators.contains(communicator)) return;

    communicator->moveToThread(this->thread());
    communicator->setParent(this);
    d->communicators.append(communicator);

    for (int id: d->descriptedLinks.keys())
    {
        if (communicator->availableProtocols().contains(d->descriptedProtocols.value(id)))
        {
            communicator->addLink(d->descriptedLinks[id]);
        }
    }
}

void CommunicatorWorker::deleteCommunicatorImpl(AbstractCommunicator* communicator)
{
    if (!d->communicators.removeOne(communicator)) return;

    disconnect(communicator, 0, this, 0);

    for (AbstractLink* link: d->descriptedLinks.values())
    {
        communicator->removeLink(link);
    }

    delete communicator;
}

void CommunicatorWorker::updateLinkImpl(int linkId, const LinkFactoryPtr& factory,
                                        bool autoconnect, const QString& protocol)
{
    d->descriptedProtocols[linkId] = protocol;

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
        connect(link, &AbstractLink::connectedChanged, this, [this, linkId](bool connected) {
            emit linkStatusChanged(linkId, connected); });
        connect(link, &AbstractLink::dataReceived, this, [this, linkId]() { emit linkRecv(linkId); });
        connect(link, &AbstractLink::dataSent, this, [this, linkId]() { emit linkSent(linkId); });
        connect(link, &AbstractLink::errored, this,
                [this, linkId](const QString& error) { emit linkErrored(linkId, error); });

        d->descriptedLinks[linkId] = link;

        if (autoconnect)
        {
            link->connectLink();
            emit linkStatusChanged(linkId, link->isConnected());
        }
    }

    for (AbstractCommunicator* communicator: d->communicators)
    {
        if (communicator->availableProtocols().contains(protocol) &&
            !communicator->links().contains(link))
        {
            communicator->addLink(link);
            continue;
        }
        else communicator->removeLink(link);
    }
}

void CommunicatorWorker::removeLinkImpl(int linkId)
{
    if (d->descriptedLinks.contains(linkId))
    {
        AbstractLink* link = d->descriptedLinks.take(linkId);

        for (AbstractCommunicator* communicator: d->communicators)
        {
            communicator->removeLink(link);
        }
        delete link;
    }
}

void CommunicatorWorker::setLinkConnectedImpl(int linkId, bool connected)
{
    AbstractLink* link = d->descriptedLinks[linkId];
    if (link) link->setConnected(connected);
}

void CommunicatorWorker::timerEvent(QTimerEvent* event)
{
    if (event->timerId() != d->statisticsTimer) return QObject::timerEvent(event);

    for (int id: d->descriptedLinks.keys())
    {
        AbstractLink* link = d->descriptedLinks[id];

        emit linkStatisticsChanged(id, QTime::currentTime().msecsSinceStartOfDay(),
                                   link->takeBytesReceived(), link->takeBytesSent());
    }
}

