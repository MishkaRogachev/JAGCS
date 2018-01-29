#include "connection_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "link_description.h"

#include "service_registry.h"
#include "communication_service.h"

using namespace presentation;

class ConnectionPresenter::Impl
{
public:
    domain::CommunicationService* service = domain::ServiceRegistry::communicationService();
};

ConnectionPresenter::ConnectionPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
//    connect(d->service, &domain::CommunicationService::linkStatisticsChanged,
//            this, &ConnectionPresenter::updateStatus);
}

ConnectionPresenter::~ConnectionPresenter()
{}

void ConnectionPresenter::updateStatus()
{
    bool connected = false;
    qreal bytesRecv = 0;
    qreal bytesSent = 0;

//    for (const dao::LinkDescriptionPtr& link: d->service->descriptions())
//    {
//        if (!link->bytesRecv().isEmpty()) bytesRecv += link->bytesRecv().last();
//        if (!link->bytesSent().isEmpty()) bytesSent += link->bytesSent().last();
//        if (!connected && link->isConnected()) connected = true;
//    }

    this->setViewProperty(PROPERTY(connected), connected);
    this->setViewProperty(PROPERTY(bytesRecv), bytesRecv);
    this->setViewProperty(PROPERTY(bytesSent), bytesSent);
}

void ConnectionPresenter::setConnected(bool connected)
{
    for (const dao::LinkDescriptionPtr& link: d->service->descriptions())
    {
        if (link->isConnected() == connected) continue;

        d->service->setLinkConnected(link, connected);
    }
}

