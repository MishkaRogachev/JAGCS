#include "abstract_communicator.h"

// Qt
#include <QDebug>

// Internal
#include "abstract_link.h"

using namespace comm;

AbstractCommunicator::AbstractCommunicator(QObject* parent):
    QObject(parent)
{
    qRegisterMetaType<Protocol>("Protocol");
}

QList<AbstractLink*> AbstractCommunicator::links() const
{
    return m_links;
}

void AbstractCommunicator::sendDataAllLinks(const QByteArray& data)
{
    for (AbstractLink* link: m_links)
    {
        if (link->isConnected()) link->sendData(data);
    }
}

void AbstractCommunicator::addLink(AbstractLink* link)
{
    m_links.append(link);

    connect(link, &AbstractLink::dataReceived,
            this, &AbstractCommunicator::onDataReceived);
    emit linkAdded(link);
}

void AbstractCommunicator::removeLink(AbstractLink* link)
{
    m_links.removeOne(link);

    disconnect(link, &AbstractLink::dataReceived,
               this, &AbstractCommunicator::onDataReceived);
    emit linkRemoved(link);
}
