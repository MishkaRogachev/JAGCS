#include "communication_service.h"

// Qt
#include <QThread>
#include <QMap>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "link_description.h"
#include "link_statistics.h"
#include "db_links_repository.h"
#include "description_link_factory.h"
#include "communicator_worker.h"

#include "notification_bus.h"
#include "db_manager.h"

using namespace domain;

class CommunicationService::Impl
{
public:
    QMap<int, dto::LinkStatisticsPtr> linkStatistics;
    QMap<ICommunicationPlugin*, data_source::AbstractCommunicator*> pluginCommunicators;

    data_source::ILinksRepository* linksRepository;
    QThread* commThread;
    CommunicatorWorker* commWorker;

    dto::LinkStatisticsPtr getlinkStatistics(int linkId)
    {
        if (!linkStatistics.contains(linkId))
        {
            linkStatistics[linkId] = dto::LinkStatisticsPtr::create();
            linkStatistics[linkId]->setLinkId(linkId);
        }
        return linkStatistics[linkId];
    }
};

CommunicationService::CommunicationService(SerialDeviceService* serialDeviceService, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    qRegisterMetaType<dto::LinkDescriptionPtr>("dto::LinkDescriptionPtr");
    qRegisterMetaType<dto::LinkDescription::Parameter>("dto::LinkDescription::Parameter");
    qRegisterMetaType<dto::LinkDescription::Type>("dto::LinkDescription::Type");
    qRegisterMetaType<dto::LinkStatisticsPtr>("dto::LinkStatisticsPtr");
    qRegisterMetaType<data_source::LinkFactoryPtr>("data_source::LinkFactoryPtr");

    d->linksRepository = new data_source::DbLinksRepository(dbManager->provider(), this);
    connect(d->linksRepository, &data_source::ILinksRepository::descriptionAdded,
            this, &CommunicationService::descriptionAdded);
    connect(d->linksRepository, &data_source::ILinksRepository::descriptionRemoved,
            this, &CommunicationService::descriptionRemoved);
    connect(d->linksRepository, &data_source::ILinksRepository::descriptionChanged,
            this, &CommunicationService::descriptionChanged);

    d->commThread = new QThread(this);
    d->commThread->setObjectName("Communication thread");

    d->commWorker = new CommunicatorWorker(serialDeviceService);
    d->commWorker->moveToThread(d->commThread);
    d->commThread->start();

    connect(d->commThread, &QThread::finished, d->commWorker, &QObject::deleteLater);
    connect(d->commWorker, &CommunicatorWorker::linkStatusChanged,
            this, &CommunicationService::onLinkConnectedChanged);
    connect(d->commWorker, &CommunicatorWorker::linkStatisticsChanged,
            this, &CommunicationService::onLinkStatisticsChanged);
    connect(d->commWorker, &CommunicatorWorker::linkSent,
            this, &CommunicationService::linkSent);
    connect(d->commWorker, &CommunicatorWorker::linkRecv,
            this, &CommunicationService::linkRecv);
    connect(d->commWorker, &CommunicatorWorker::linkErrored,
            this, &CommunicationService::onLinkErrored);

    for (const dto::LinkDescriptionPtr& description: d->linksRepository->descriptions())
    {
        data_source::LinkFactoryPtr factory(new data_source::DescriptionLinkFactory(description));
        d->commWorker->updateLink(description->id(), factory, description->isAutoConnect(),
                                  description->protocol());
    }
}

CommunicationService::~CommunicationService()
{
    d->commThread->quit();
    d->commThread->wait();

    for (const dto::LinkDescriptionPtr& description: d->linksRepository->descriptions())
    {
        description->setAutoConnect(description->isConnected());
        d->linksRepository->save(description);
    }
}

dto::LinkDescriptionPtr CommunicationService::description(int id) const
{
    return d->linksRepository->description(id);
}

dto::LinkDescriptionPtrList CommunicationService::descriptions() const
{
    return d->linksRepository->descriptions();
}

dto::LinkStatisticsPtr CommunicationService::statistics(int descriptionId) const
{
     return d->linkStatistics.value(descriptionId);
}

dto::LinkStatisticsPtrList CommunicationService::statistics() const
{
    return d->linkStatistics.values();
}

void CommunicationService::addPlugin(ICommunicationPlugin* plugin)
{
    data_source::AbstractCommunicator* communicator = plugin->createCommunicator();
    if (!communicator) return;

    d->pluginCommunicators[plugin] = communicator;

    communicator->moveToThread(d->commThread);
    d->commWorker->addCommunicator(communicator);

    emit availableProtocolsChanged();
}

void CommunicationService::removePlugin(ICommunicationPlugin* plugin)
{
    if (!d->pluginCommunicators.contains(plugin)) return;

    data_source::AbstractCommunicator* communicator = d->pluginCommunicators.take(plugin);
    d->commWorker->deleteCommunicator(communicator);

    emit availableProtocolsChanged();
}

QStringList CommunicationService::availableProtocols() const
{
    QStringList protocols;

    for (data_source::AbstractCommunicator* communicator: d->pluginCommunicators.values())
    {
        protocols.append(communicator->availableProtocols());
    }

    return protocols;
}

bool CommunicationService::save(const dto::LinkDescriptionPtr& description)
{
    if (!d->linksRepository->save(description)) return false;

    data_source::LinkFactoryPtr factory(new data_source::DescriptionLinkFactory(description));
    d->commWorker->updateLink(description->id(), factory,
                              description->isAutoConnect(), description->protocol());
    return true;
}

bool CommunicationService::remove(const dto::LinkDescriptionPtr& description)
{
    if (!d->linksRepository->remove(description)) return false;

    d->commWorker->removeLink(description->id());
    return true;
}

void CommunicationService::setLinkConnected(int descriptionId, bool connected)
{
    d->commWorker->setLinkConnected(descriptionId, connected);

    dto::LinkDescriptionPtr description = this->description(descriptionId);
    if (description) description->setAutoConnect(connected);
}

void CommunicationService::onLinkConnectedChanged(int descriptionId, bool connected)
{
    dto::LinkDescriptionPtr description = this->description(descriptionId);

    if (description->isConnected() != connected)
    {
        notificationBus->notify(tr("Link") + " " + description->name(),
                             connected ? tr("Connection established") : tr("Connection lost"),
                             connected ? dto::Notification::Positive : dto::Notification::Warning);
        description->setConnected(connected);

        emit linkConnectedChanged(description, connected);
    }
}

void CommunicationService::onLinkStatisticsChanged(int descriptionId,
                                                   int timestamp,
                                                   int bytesReceivedSec,
                                                   int bytesSentSec)
{
    dto::LinkStatisticsPtr statistics = d->getlinkStatistics(descriptionId);

    statistics->setTimestamp(timestamp);
    statistics->setBytesRecv(bytesReceivedSec);
    statistics->setBytesSent(bytesSentSec);

    emit linkStatisticsChanged(statistics);
}

void CommunicationService::onLinkErrored(int descriptionId, const QString& error)
{
    dto::LinkDescriptionPtr description = this->description(descriptionId);

    notificationBus->notify(tr("Link") + " " + description->name(),
                            error, dto::Notification::Warning);
}

