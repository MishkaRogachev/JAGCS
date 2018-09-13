#include "udp_link_vm.h"

// Qt
#include <QDebug>

// Internal
#include "communication_service.h"

namespace
{
    const QString separator = ";";
}

using namespace presentation;

UdpLinkVm::UdpLinkVm(QObject* parent):
    SocketLinkVm(parent)
{}

QStringList UdpLinkVm::endpoints() const
{
    QStringList endpoints;

    if (m_description)
    {
        for (const QString& endpoint: m_description->parameter(
                 dto::LinkDescription::Endpoints).toString().split(::separator))
        {
            endpoints.append(endpoint);
        }
    }

    return endpoints;
}

bool UdpLinkVm::autoAdd() const
{
    return m_description && m_description->parameter(dto::LinkDescription::UdpAutoResponse).toBool();
}

void UdpLinkVm::setEndpoints(const QStringList& endpoints)
{
    if (m_description.isNull()) return;

    m_description->setParameter(dto::LinkDescription::Endpoints, endpoints.join(::separator));
    if (m_commService->save(m_description)) emit endpointsChanged();
}

void UdpLinkVm::setAutoAdd(bool autoAdd)
{
    if (m_description.isNull() ||
        m_description->parameter(dto::LinkDescription::UdpAutoResponse) == autoAdd) return;

    m_description->setParameter(dto::LinkDescription::UdpAutoResponse, autoAdd);
    if (m_commService->save(m_description)) emit autoAddChanged();
}

void UdpLinkVm::changed()
{
    SocketLinkVm::changed();

    emit endpointsChanged();
    emit autoAddChanged();
}
