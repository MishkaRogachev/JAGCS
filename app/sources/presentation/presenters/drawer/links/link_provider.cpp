#include "link_provider.h"

// Qt
#include <QMap>
#include <QVariant>
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

LinkProvider::LinkProvider(QObject* parent):
    QObject(parent),
    m_commService(serviceRegistry->communicationService())
{
    connect(m_commService, &domain::CommunicationService::availableProtocolsChanged,
            this, &LinkProvider::availableProtocolsChanged);

    connect(m_commService, &domain::CommunicationService::descriptionChanged, this,
            [this](const dto::LinkDescriptionPtr& description) {
        if (m_description == description) emit descriptionChanged();
    });

    connect(m_commService, &domain::CommunicationService::linkConnectedChanged, this,
            [this](const dto::LinkDescriptionPtr& description) {
        if (m_description == description) emit connectedChanged();
    });
    connect(m_commService, &domain::CommunicationService::linkStatisticsChanged, this,
            [this](const dto::LinkStatisticsPtr& statistics) {
        if (m_description && m_description->id() == statistics->linkId())

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

dto::LinkDescriptionPtr LinkProvider::description() const
{
    return m_description;
}

QString LinkProvider::name() const
{
    return m_description ? m_description->name() : tr("None");
}

QString LinkProvider::protocol() const
{
    return m_description ? m_description->protocol() : tr("Unknown");
}

dto::LinkDescription::Type LinkProvider::type() const
{
    return m_description ? m_description->type() : dto::LinkDescription::UnknownType;
}

bool LinkProvider::isConnected() const
{
    return m_description && m_description->isConnected();
}

float LinkProvider::bytesRecv() const
{
    return m_statistics ? m_statistics->bytesRecv() : 0;
}

float LinkProvider::bytesSent() const
{
    return m_statistics ? m_statistics->bytesSent() : 0;
}

QStringList LinkProvider::availableProtocols() const
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

QVariant LinkProvider::parameter(dto::LinkDescription::Parameter key) const
{
    return m_description ? m_description->parameter(key) : QVariant();
}

void LinkProvider::setDescription(const dto::LinkDescriptionPtr& description)
{
    if (m_description == description) return;

    m_description = description;

    emit descriptionChanged();
    emit connectedChanged();
    emit statisticsChanged();
}

void LinkProvider::setConnected(bool connected)
{
    if (m_description) m_commService->setLinkConnected(m_description->id(), connected);
}

void LinkProvider::remove()
{
    if (m_description) m_commService->remove(m_description);
}

void LinkProvider::setName(const QString& name)
{
    if (m_description.isNull()) return;

    m_description->setName(name);
    m_commService->save(m_description);
}

void LinkProvider::setProtocol(const QString& protocol)
{
    if (m_description.isNull()) return;

    m_description->setProtocol(protocol);
    m_commService->save(m_description);
}

void LinkProvider::setParameter(dto::LinkDescription::Parameter key, const QVariant& parameter)
{
    if (m_description.isNull()) return;
    
    m_description->setParameter(key, parameter);
    m_commService->save(m_description);
}
