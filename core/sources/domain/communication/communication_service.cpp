#include "communication_service.h"

// Qt
#include <QThread>
#include <QMap>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "link_description.h"
#include "db_link_repository.h"
#include "description_link_factory.h"
#include "communicator_worker.h"

#include "notification_bus.h"
#include "db_manager.h"

using namespace domain;

class CommunicationService::Impl
{
public:
    QMap<ICommunicationPlugin*, data_source::AbstractCommunicator*> pluginCommunicators;

    data_source::ILinkRepository* linkRepository;
    QThread* commThread;
    CommunicatorWorker* commWorker;
};

CommunicationService::CommunicationService(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    qRegisterMetaType<dto::LinkDescriptionPtr>("dto::LinkDescriptionPtr");
    qRegisterMetaType<dto::LinkDescription::Parameter>("dto::LinkDescription::Parameter");
    qRegisterMetaType<dto::LinkDescription::Type>("dto::LinkDescription::Type");
    qRegisterMetaType<data_source::LinkFactoryPtr>("data_source::LinkFactoryPtr");

    d->linkRepository = new data_source::DbLinkRepository(dbManager->provider(), this);
    connect(d->linkRepository, &data_source::ILinkRepository::descriptionAdded,
            this, &CommunicationService::descriptionAdded);
    connect(d->linkRepository, &data_source::ILinkRepository::descriptionRemoved,
            this, &CommunicationService::descriptionRemoved);
    connect(d->linkRepository, &data_source::ILinkRepository::descriptionChanged,
            this, &CommunicationService::descriptionChanged);

    d->commThread = new QThread(this);
    d->commThread->setObjectName("Communication thread");

    d->commWorker = new CommunicatorWorker();
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

    for (const dto::LinkDescriptionPtr& description: d->linkRepository->descriptions())
    {
        data_source::LinkFactoryPtr factory(new data_source::DescriptionLinkFactory(description));
//        d->commWorker->updateLink(description->id(), factory, description->isAutoConnect(),
//                                  description->protocol());
    }
}

CommunicationService::~CommunicationService()
{
    d->commThread->quit();
    d->commThread->wait();

    for (const dto::LinkDescriptionPtr& description: d->linkRepository->descriptions())
    {
        description->setAutoConnect(description->isConnected());
        d->linkRepository->save(description);
    }
}

dto::LinkDescriptionPtr CommunicationService::description(int id) const
{
    return d->linkRepository->description(id);
}

dto::LinkDescriptionPtrList CommunicationService::descriptions() const
{
    return d->linkRepository->descriptions();
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
    if (!d->linkRepository->save(description)) return false;

    data_source::LinkFactoryPtr factory(new data_source::DescriptionLinkFactory(description));
//    d->commWorker->updateLink(description->id(), factory,
//                              description->isAutoConnect(), description->protocol());
    return true;
}

bool CommunicationService::remove(const dto::LinkDescriptionPtr& description)
{
    if (!d->linkRepository->remove(description)) return false;

//    d->commWorker->removeLink(description->id());
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
//    dto::LinkStatisticsPtr statistics = d->getlinkStatistics(descriptionId);

//    statistics->setTimestamp(timestamp);
//    statistics->setBytesRecv(bytesReceivedSec);
//    statistics->setBytesSent(bytesSentSec);

//    emit linkStatisticsChanged(statistics);
}

void CommunicationService::onLinkErrored(int descriptionId, const QString& error)
{
    dto::LinkDescriptionPtr description = this->description(descriptionId);

    notificationBus->notify(tr("Link") + " " + description->name(),
                            error, dto::Notification::Warning);
}

