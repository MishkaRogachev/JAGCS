#include "link_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "link_description.h"
#include "link_statistics.h"

#include "service_registry.h"
#include "communication_service.h"

using namespace presentation;

LinkPresenter::LinkPresenter(QObject* parent):
    BasePresenter(parent),
    m_service(serviceRegistry->communicationService())
{
    connect(m_service, &domain::CommunicationService::descriptionChanged, this,
            [this](const dto::LinkDescriptionPtr& description) {
        if (m_description == description) this->updateLink();
    });
    connect(m_service, &domain::CommunicationService::linkStatusChanged, this,
            [this](const dto::LinkDescriptionPtr& description) {
        if (m_description == description) this->updateStatus();
    });
    connect(m_service, &domain::CommunicationService::linkStatisticsChanged, this,
            [this](const dto::LinkStatisticsPtr& statistics) {
        if (m_description->id() == statistics->linkId()) this->updateStatistics(statistics);
    });
}

void LinkPresenter::setLink(int id)
{
    m_description = m_service->description(id);

    this->updateLink();
    this->updateStatus();
}

void LinkPresenter::updateLink()
{
    if (m_description.isNull()) return;

    this->setViewProperty(PROPERTY(type), m_description->type());
    this->setViewProperty(PROPERTY(name), m_description->name());
}

void LinkPresenter::updateStatus()
{
    this->setViewProperty(PROPERTY(connected), m_description && m_description->isConnected());
    this->setViewProperty(PROPERTY(protocol), m_description ? m_description->protocol() :
                                                              dto::LinkDescription::UnknownProtocol);
}

void LinkPresenter::setConnected(bool connected)
{
    if (m_description.isNull()) return;

    m_service->setLinkConnected(m_description, connected);
}

void LinkPresenter::remove()
{
    if (m_description.isNull()) return;

    m_service->remove(m_description);
}

void LinkPresenter::updateStatistics(const dto::LinkStatisticsPtr& statistics)
{
    this->setViewProperty(PROPERTY(bytesRecv), statistics->bytesRecv());
    this->setViewProperty(PROPERTY(bytesSent), statistics->bytesSent());
}
