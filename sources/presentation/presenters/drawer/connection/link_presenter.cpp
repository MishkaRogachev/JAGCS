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
        if (m_link == description) this->updateLink();
    });
    connect(m_service, &domain::CommunicationService::linkStatusChanged, this,
            [this](const dto::LinkDescriptionPtr& description) {
        if (m_link == description) this->updateStatus();
    });
    connect(m_service, &domain::CommunicationService::linkStatisticsChanged, this,
            [this](const dto::LinkStatisticsPtr& statistics) {
        if (m_link && m_link->id() == statistics->linkId()) this->updateStatistics(statistics);
    });
    connect(m_service, &domain::CommunicationService::linkSent,
            this, [this](int linkId) {
        if (m_link && m_link->id() == linkId) this->setViewProperty(PROPERTY(sent), true);
    });
    connect(m_service, &domain::CommunicationService::linkRecv,
            this, [this](int linkId) {
        if (m_link && m_link->id() == linkId) this->setViewProperty(PROPERTY(recv), true);
    });
}

void LinkPresenter::setLink(int id)
{
    m_link = m_service->description(id);

    this->updateLink();
    this->updateStatus();
}

void LinkPresenter::updateLink()
{
    this->setViewProperty(PROPERTY(type), m_link ? m_link->type() :
                                                   dto::LinkDescription::UnknownType);
    this->setViewProperty(PROPERTY(name), m_link ? m_link->name() : QString());
}

void LinkPresenter::updateStatus()
{
    this->setViewProperty(PROPERTY(connected), m_link && m_link->isConnected());
    this->setViewProperty(PROPERTY(protocol), m_link ? m_link->protocol() :
                                                       dto::LinkDescription::UnknownProtocol);
}

void LinkPresenter::setConnected(bool connected)
{
    if (m_link) m_service->setLinkConnected(m_link, connected);
}

void LinkPresenter::remove()
{
    if (m_link) m_service->remove(m_link);
}

void LinkPresenter::updateStatistics(const dto::LinkStatisticsPtr& statistics)
{
    this->setViewProperty(PROPERTY(bytesRecv), statistics->bytesRecv());
    this->setViewProperty(PROPERTY(bytesSent), statistics->bytesSent());
}
