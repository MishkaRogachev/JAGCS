#include "link_vm.h"

// Qt
#include <QDebug>

// Internal
#include "link_statistics.h"

#include "service_registry.h"
#include "communication_service.h"

namespace
{
    const QString separator = ",";
}

using namespace presentation;

LinkVm::LinkVm(QObject* parent):
    QObject(parent),
    m_commService(serviceRegistry->communicationService())
{
    connect(m_commService, &domain::CommunicationService::availableProtocolsChanged,
            this, &LinkVm::availableProtocolsChanged);

    connect(m_commService, &domain::CommunicationService::descriptionChanged, this,
            [this](const dto::LinkDescriptionPtr& description) {
        if (m_description == description) emit linkChanged();
    });

    connect(m_commService, &domain::CommunicationService::linkConnectedChanged, this,
            [this](const dto::LinkDescriptionPtr& description) {
        if (m_description == description) emit connectedChanged();
    });
    connect(m_commService, &domain::CommunicationService::linkStatisticsChanged, this,
            [this](const dto::LinkStatisticsPtr& statistics) {
        if (m_description.isNull() || m_description->id() != statistics->linkId()) return;

        m_statistics = statistics;
        emit statisticsChanged();
    });
    connect(m_commService, &domain::CommunicationService::linkSent,
            this, [this](int descriptionId) {
        if (m_description && m_description->id() == descriptionId) emit sent();
    });
    connect(m_commService, &domain::CommunicationService::linkRecv,
            this, [this](int descriptionId) {
        if (m_description && m_description->id() == descriptionId) emit recv();
    });
}

QString LinkVm::name() const
{
    return m_description ? m_description->name() : tr("None");
}

QString LinkVm::protocol() const
{
    return m_description ? m_description->protocol() : tr("Unknown");
}

dto::LinkDescription::Type LinkVm::type() const
{
    return m_description ? m_description->type() : dto::LinkDescription::UnknownType;
}

bool LinkVm::isConnected() const
{
    return m_description && m_description->isConnected();
}

float LinkVm::bytesRecv() const
{
    return m_statistics ? m_statistics->bytesRecv() : 0;
}

float LinkVm::bytesSent() const
{
    return m_statistics ? m_statistics->bytesSent() : 0;
}

QStringList LinkVm::availableProtocols() const
{
    QStringList protocols;

    protocols.append(QString());
    protocols.append(m_commService->availableProtocols());

    if (m_description && !protocols.contains(m_description->protocol()))
    {
        protocols.append(m_description->protocol());
    }

    return protocols;
}

void LinkVm::setDescription(const dto::LinkDescriptionPtr& description)
{
    if (m_description == description) return;

    m_description = description;

    emit linkChanged();
    emit connectedChanged();
    emit statisticsChanged();
}

void LinkVm::setConnected(bool connected)
{
    if (m_description) m_commService->setLinkConnected(m_description->id(), connected);
}

void LinkVm::remove()
{
    if (m_description) m_commService->remove(m_description);
}

void LinkVm::setName(const QString& name)
{
    if (m_description.isNull() || m_description->name() == name) return;

    m_description->setName(name);
    m_commService->save(m_description);
}

void LinkVm::setProtocol(const QString& protocol)
{
    if (m_description.isNull() || m_description->protocol() == protocol) return;

    m_description->setProtocol(protocol);
    m_commService->save(m_description);
}
