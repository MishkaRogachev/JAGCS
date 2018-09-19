#include "tcp_link_vm.h"

// Qt
#include <QDebug>

// Internal
#include "communication_service.h"

using namespace presentation;

TcpLinkVm::TcpLinkVm(QObject* parent):
    SocketLinkVm(parent)
{
    connect(this, &LinkVm::linkChanged, this, &TcpLinkVm::tcpLinkChanged);
}

QString TcpLinkVm::address() const
{
    return m_description ? m_description->parameter(data_source::LinkDescription::Address).toString() : QString();
}

void TcpLinkVm::setAddress(const QString& address)
{
    if (m_description.isNull() ||
        m_description->parameter(data_source::LinkDescription::Address) == address) return;

    m_description->setParameter(data_source::LinkDescription::Address, address);
    m_commService->save(m_description);
}

