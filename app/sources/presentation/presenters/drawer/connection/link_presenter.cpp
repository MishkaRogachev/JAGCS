#include "link_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "link_statistics.h"

#include "service_registry.h"
#include "communication_service.h"

using namespace presentation;

class LinkPresenter::Impl
{
public:
    domain::CommunicationService* const service = serviceRegistry->communicationService();
    dto::LinkDescriptionPtr description;
    dto::LinkStatisticsPtr statistics;
};

LinkPresenter::LinkPresenter(const dto::LinkDescriptionPtr& description, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->description = description;

    connect(d->service, &domain::CommunicationService::descriptionChanged, this,
            [this](const dto::LinkDescriptionPtr& description) {
        if (d->description == description) emit propertiesChanged();
    });

    connect(d->service, &domain::CommunicationService::linkConnectedChanged, this,
            [this](const dto::LinkDescriptionPtr& description) {
        if (d->description == description) emit connectedChanged();
    });
    connect(d->service, &domain::CommunicationService::linkStatisticsChanged, this,
            [this](const dto::LinkStatisticsPtr& statistics) {
        if (d->description && d->description->id() == statistics->linkId())

            d->statistics = statistics;
            emit statisticsChanged();
    });
    connect(d->service, &domain::CommunicationService::linkSent,
            this, [this](int descriptionId) {
        if (d->description && d->description->id() == descriptionId) emit sent();
    });
    connect(d->service, &domain::CommunicationService::linkRecv,
            this, [this](int descriptionId) {
        if (d->description && d->description->id() == descriptionId) emit recv();
    });
}

LinkPresenter::~LinkPresenter()
{}

QString LinkPresenter::name() const
{
    return d->description ? d->description->name() : tr("None");
}

QString LinkPresenter::protocol() const
{
    return d->description ? d->description->protocol() : tr("Unknown");
}

dto::LinkDescription::Type LinkPresenter::type() const
{
    return d->description ? d->description->type() : dto::LinkDescription::UnknownType;
}

bool LinkPresenter::isConnected() const
{
    return d->description && d->description->isConnected();
}

float LinkPresenter::bytesRecv() const
{
    return d->statistics ? d->statistics->bytesRecv() : 0;
}

float LinkPresenter::bytesSent() const
{
    return d->statistics ? d->statistics->bytesSent() : 0;
}

void LinkPresenter::setDescription(const dto::LinkDescriptionPtr& description)
{
    if (d->description == description) return;

    d->description = description;

    emit propertiesChanged();
    emit connectedChanged();
    emit statisticsChanged();
}

void LinkPresenter::setConnected(bool connected)
{
    if (d->description) d->service->setLinkConnected(d->description->id(), connected);
}

void LinkPresenter::remove()
{
    if (d->description) d->service->remove(d->description);
}

void LinkPresenter::setName(const QString& name)
{
    if (d->description.isNull()) return;

    d->description->setName(name);
    d->service->save(d->description);
}

void LinkPresenter::setProtocol(const QString& protocol)
{
    if (d->description.isNull()) return;

    d->description->setProtocol(protocol);
    d->service->save(d->description);
}
