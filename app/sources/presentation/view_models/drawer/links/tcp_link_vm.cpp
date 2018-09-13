#include "tcp_link_vm.h"

// Qt
#include <QDebug>

// Internal
#include "communication_service.h"

using namespace presentation;

TcpLinkVm::TcpLinkVm(QObject* parent):
    SocketLinkVm(parent)
{}

QString TcpLinkVm::address() const
{
    return m_description ? m_description->parameter(dto::LinkDescription::Address).toString() : QString();
}

void TcpLinkVm::setAddress(const QString& address)
{
    if (m_description.isNull() ||
        m_description->parameter(dto::LinkDescription::Address) == address) return;

    m_description->setParameter(dto::LinkDescription::Address, address);
    if (m_commService->save(m_description)) emit addressChanged();
}

void TcpLinkVm::changed()
{
    SocketLinkVm::changed();

    emit addressChanged();
}
