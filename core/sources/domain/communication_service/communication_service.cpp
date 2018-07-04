#include "communication_service.h"

// Qt
#include <QThread>
#include <QMap>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "link_description.h"
#include "link_statistics.h"

#include "generic_repository.h"

#include "serial_ports_service.h"

#include "description_link_factory.h"
#include "mavlink_communicator_factory.h"
#include "communicator_worker.h"

#include "notification_bus.h"

using namespace domain;

class CommunicationService::Impl
{
public:
    SerialPortService* serialPortService;
    QMap<dto::LinkDescriptionPtr, QString> descriptedDevices;
    QMap<int, dto::LinkStatisticsPtr> linkStatistics;

    QThread* commThread;
    CommunicatorWorker* commWorker;

    GenericRepository<dto::LinkDescription> linkRepository;

    Impl():
        linkRepository("links")
    {}

    void loadDescriptions(const QString& condition = QString())
    {
        for (int id: linkRepository.selectId(condition)) linkRepository.read(id);
    }

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

CommunicationService::CommunicationService(SerialPortService* serialPortService, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    qRegisterMetaType<dto::LinkDescriptionPtr>("dto::LinkDescriptionPtr");
    qRegisterMetaType<dto::LinkDescription::Protocol>("dto::LinkDescription::Protocol");
    qRegisterMetaType<comm::LinkFactoryPtr>("comm::LinkFactoryPtr");

    d->serialPortService = serialPortService;
    connect(serialPortService, &SerialPortService::devicesChanged,
            this, &CommunicationService::onDevicesChanged);

    d->commThread = new QThread(this);
    d->commThread->setObjectName("Communication thread");

    d->commWorker = new CommunicatorWorker();
    d->commWorker->moveToThread(d->commThread);
    d->commThread->start();

    connect(d->commThread, &QThread::finished, d->commWorker, &QObject::deleteLater);
    connect(d->commWorker, &CommunicatorWorker::linkStatusChanged,
            this, &CommunicationService::onLinkStatusChanged);
    connect(d->commWorker, &CommunicatorWorker::linkStatisticsChanged,
            this, &CommunicationService::onLinkStatisticsChanged);
    connect(d->commWorker, &CommunicatorWorker::mavLinkStatisticsChanged,
            this, &CommunicationService::onMavLinkStatisticsChanged);
    connect(d->commWorker, &CommunicatorWorker::mavLinkProtocolChanged,
            this, &CommunicationService::onMavlinkProtocolChanged);
    connect(d->commWorker, &CommunicatorWorker::linkSent,
            this, &CommunicationService::linkSent);
    connect(d->commWorker, &CommunicatorWorker::linkRecv,
            this, &CommunicationService::linkRecv);
    connect(d->commWorker, &CommunicatorWorker::linkErrored,
            this, &CommunicationService::onLinkErrored);

    d->loadDescriptions();
}

CommunicationService::~CommunicationService()
{
    for (const dto::LinkDescriptionPtr& description: this->descriptions())
    {
        description->setAutoConnect(description->isConnected());
        this->save(description);

        if (d->descriptedDevices.contains(description))
        {
            d->serialPortService->releaseDevice(d->descriptedDevices.take(description));
        }
    }

    d->commThread->quit();
    d->commThread->wait();
}

dto::LinkDescriptionPtr CommunicationService::description(int id) const
{
    return d->linkRepository.read(id);
}

dto::LinkDescriptionPtrList CommunicationService::descriptions() const
{
    return d->linkRepository.loadedEntities();
}

dto::LinkStatisticsPtr CommunicationService::statistics(int descriptionId) const
{
     return d->linkStatistics.value(descriptionId);
}

dto::LinkStatisticsPtrList CommunicationService::statistics() const
{
    return d->linkStatistics.values();
}

void CommunicationService::init()
{
    // TODO: different link protocols
    comm::MavLinkCommunicatorFactory commFactory(
                settings::Provider::value(settings::communication::systemId).toInt(),
                settings::Provider::value(settings::communication::componentId).toInt());

    comm::AbstractCommunicator* communicator = commFactory.create();
    communicator->moveToThread(d->commThread);

    d->commWorker->setCommunicator(communicator);

    for (const dto::LinkDescriptionPtr& description: this->descriptions())
    {
        comm::LinkFactoryPtr factory(new comm::DescriptionLinkFactory(description));
        d->commWorker->updateLink(description->id(),
                                  factory, description->isAutoConnect());

        QString device = description->parameter(dto::LinkDescription::Device).toString();
        if (description->type() == dto::LinkDescription::Serial && device.length() > 0)
        {
            d->serialPortService->holdDevice(device);
            d->descriptedDevices[description] = device;
        }
    }
}

bool CommunicationService::save(const dto::LinkDescriptionPtr& description)
{
    bool isNew = description->id() == 0;
    if (!d->linkRepository.save(description)) return false;

    comm::LinkFactoryPtr factory(new comm::DescriptionLinkFactory(
                                     description));
    d->commWorker->updateLink(description->id(),
                              factory, description->isAutoConnect());

    QString device = description->parameter(dto::LinkDescription::Device).toString();
    if (d->descriptedDevices.contains(description) && device != d->descriptedDevices[description])
    {
        d->serialPortService->releaseDevice(d->descriptedDevices.take(description));
    }

    isNew ? descriptionAdded(description) : descriptionChanged(description);

    if (description->type() == dto::LinkDescription::Serial &&
        device.length() > 0 && !d->descriptedDevices.contains(description))
    {
        d->serialPortService->holdDevice(device);
        d->descriptedDevices[description] = device;
    }

    return true;
}

bool CommunicationService::remove(const dto::LinkDescriptionPtr& description)
{
    if (!d->linkRepository.remove(description)) return false;

    d->commWorker->removeLink(description->id());

    if (d->descriptedDevices.contains(description))
    {
        d->serialPortService->releaseDevice(d->descriptedDevices.take(description));
    }

    if (d->linkStatistics.contains(description->id()))
    {
        d->linkStatistics.remove(description->id());
    }

    emit descriptionRemoved(description);

    return true;
}

void CommunicationService::setLinkConnected(const dto::LinkDescriptionPtr& description,
                                            bool connected)
{
    d->commWorker->setLinkConnected(description->id(), connected);

    description->setAutoConnect(connected);
}

void CommunicationService::onLinkStatusChanged(int linkId, bool connected)
{
    dto::LinkDescriptionPtr description = this->description(linkId);

    if (description->isConnected() != connected)
    {
        notificationBus->notify(tr("Link") + " " + description->name(),
                             connected ? tr("Connection established") : tr("Connection lost"),
                             connected ? dto::Notification::Positive : dto::Notification::Warning);
        description->setConnected(connected);

        emit linkStatusChanged(description);
    }
}

void CommunicationService::onLinkStatisticsChanged(int linkId,
                                                   int timestamp,
                                                   int bytesReceivedSec,
                                                   int bytesSentSec)
{
    dto::LinkStatisticsPtr statistics = d->getlinkStatistics(linkId);

    statistics->setTimestamp(timestamp);
    statistics->setBytesRecv(bytesReceivedSec);
    statistics->setBytesSent(bytesSentSec);

    emit linkStatisticsChanged(statistics);
}

void CommunicationService::onMavLinkStatisticsChanged(int linkId,
                                                      int packetsReceived,
                                                      int packetsDrops)
{
    dto::LinkStatisticsPtr statistics = d->getlinkStatistics(linkId);

    statistics->setPacketsRecv(packetsReceived);
    statistics->setPacketDrops(packetsDrops);

    // TODO: No handle for MavLinkStatistics yet
}

void CommunicationService::onMavlinkProtocolChanged(int linkId,
                                                    dto::LinkDescription::Protocol protocol)
{
    dto::LinkDescriptionPtr description = this->description(linkId);
    if (description->protocol() == protocol) return;

    QString msg = tr("Unknown");
    if (protocol == dto::LinkDescription::MavLink1) msg = tr("Switched on MAVLINK v.1");
    if (protocol == dto::LinkDescription::MavLink2) msg = tr("Switched on MAVLINK v.2");

    notificationBus->notify(tr("Link") + " " + description->name(), msg);
    description->setProtocol(protocol);

    emit linkStatusChanged(description);
}

void CommunicationService::onLinkErrored(int linkId, const QString& error)
{
    dto::LinkDescriptionPtr description = this->description(linkId);

    notificationBus->notify(tr("Link") + " " + description->name(),
                            error, dto::Notification::Warning);
}

void CommunicationService::onDevicesChanged()
{
    QStringList devices = d->serialPortService->devices();

    for (const dto::LinkDescriptionPtr& description: d->descriptedDevices.keys())
    {
        if (!description->isConnected() && description->isAutoConnect() &&
            devices.contains(description->parameter(dto::LinkDescription::Device).toString()))
        {
            this->setLinkConnected(description, true);
        }
    }
}
