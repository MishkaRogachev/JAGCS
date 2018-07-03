#include "connection_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "link_description.h"
#include "link_statistics.h"

#include "service_registry.h"
#include "communication_service.h"

using namespace presentation;

class ConnectionPresenter::Impl
{
public:
    domain::CommunicationService* service = serviceRegistry->communicationService();
};

ConnectionPresenter::ConnectionPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    connect(d->service, &domain::CommunicationService::linkStatusChanged,
            this, &ConnectionPresenter::updateStatus);
    connect(d->service, &domain::CommunicationService::linkStatisticsChanged,
            this, &ConnectionPresenter::updateStatistics);
    connect(d->service, &domain::CommunicationService::linkSent,
            this, [this]() { this->setViewProperty(PROPERTY(sent), true); });
    connect(d->service, &domain::CommunicationService::linkRecv,
            this, [this]() { this->setViewProperty(PROPERTY(recv), true); });
}

ConnectionPresenter::~ConnectionPresenter()
{}

void ConnectionPresenter::updateStatus()
{
    bool connected = false;

    for (const dto::LinkDescriptionPtr& link: d->service->descriptions())
    {
        if (!link->isConnected()) continue;

        connected = true;
        break;
    }

    this->setViewProperty(PROPERTY(connected), connected);
}

void ConnectionPresenter::updateStatistics()
{
    qreal bytesRecv = 0;
    qreal bytesSent = 0;

    for (const dto::LinkStatisticsPtr& stats: d->service->statistics())
    {
        bytesRecv += stats->bytesRecv();
        bytesSent += stats->bytesSent();
    }

    this->setViewProperty(PROPERTY(bytesRecv), bytesRecv);
    this->setViewProperty(PROPERTY(bytesSent), bytesSent);
}

void ConnectionPresenter::setConnected(bool connected)
{
    for (const dto::LinkDescriptionPtr& link: d->service->descriptions())
    {
        if (link->isConnected() == connected) continue;

        d->service->setLinkConnected(link, connected);
    }
}

