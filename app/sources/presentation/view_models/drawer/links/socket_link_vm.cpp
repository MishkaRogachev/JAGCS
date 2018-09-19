#include "socket_link_vm.h"

// Qt
#include <QDebug>

// Internal
#include "communication_service.h"

using namespace presentation;

SocketLinkVm::SocketLinkVm(QObject* parent):
    LinkVm(parent)
{
    connect(this, &LinkVm::linkChanged, this, &SocketLinkVm::socketLinkChanged);
}

int SocketLinkVm::port() const
{
    return m_description ? m_description->parameter(data_source::LinkDescription::Port).toInt() : 0;
}

void SocketLinkVm::setPort(int port)
{
    if (m_description.isNull() ||
        m_description->parameter(data_source::LinkDescription::Port) == port) return;

    m_description->setParameter(data_source::LinkDescription::Port, port);
    m_commService->save(m_description);
}

