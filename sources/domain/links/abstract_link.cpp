#include "abstract_link.h"

// Internal
#include "abstract_communicator.h"

using namespace data_source;

AbstractLink::AbstractLink(QObject* parent): QObject(parent)
{}

AbstractCommunicator* AbstractLink::communicator() const
{
    return m_communicator;
}

void AbstractLink::setCommunicator(AbstractCommunicator* communicator)
{
    if (m_communicator == communicator) return;

    if (m_communicator)
    {
        disconnect(m_communicator, &AbstractCommunicator::sendData,
                   this, &AbstractLink::sendData);
    }

    if (communicator)
    {
        connect(m_communicator, &AbstractCommunicator::sendData,
                this, &AbstractLink::sendData);
    }

    m_communicator = communicator;
}

void AbstractLink::onDataReceived(const QByteArray& data)
{
    if (m_communicator) m_communicator->receiveData(data, this);
}
