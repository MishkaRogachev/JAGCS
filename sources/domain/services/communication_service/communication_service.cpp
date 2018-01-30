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
#include "generic_repository_impl.h"

#include "serial_ports_service.h"

#include "description_link_factory.h"
#include "mavlink_communicator_factory.h"
#include "communicator_worker.h"

#include "log_bus.h"

using namespace domain;

class CommunicationService::Impl
{
public:
    SerialPortService* serialPortService;
    QMap<dao::LinkDescriptionPtr, QString> descriptedDevices;
    QMap<int, dao::LinkStatisticsPtr> linkStatistics;

    QThread* commThread;
    CommunicatorWorker* commWorker;

    GenericRepository<dao::LinkDescription> linkRepository;

    Impl():
        linkRepository("links")
    {}

    void loadDescriptions(const QString& condition = QString())
    {
        for (int id: linkRepository.selectId(condition)) linkRepository.read(id);
    }

    dao::LinkStatisticsPtr getlinkStatistics(int linkId)
    {
        if (!linkStatistics.contains(linkId))
        {
            linkStatistics[linkId] = dao::LinkStatisticsPtr::create();
            linkStatistics[linkId]->setLinkId(linkId);
        }
        return linkStatistics[linkId];
    }
};

CommunicationService::CommunicationService(SerialPortService* serialPortService, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    qRegisterMetaType<dao::LinkDescriptionPtr>("dao::LinkDescriptionPtr");
    qRegisterMetaType<dao::LinkDescription::Protocol>("dao::LinkDescription::Protocol");
    qRegisterMetaType<comm::LinkFactoryPtr>("comm::LinkFactoryPtr");

    d->serialPortService = serialPortService;
    connect(serialPortService, &SerialPortService::devicesChanged,
            this, &CommunicationService::onDevicesChanged);

    d->commThread = new QThread(this);
    d->commThread->setObjectName("Communication thread");

    d->commWorker = new CommunicatorWorker();
    d->commWorker->moveToThread(d->commThread);

    connect(d->commThread, &QThread::finished, d->commWorker, &QObject::deleteLater);
    connect(d->commWorker, &CommunicatorWorker::linkStatusChanged,
            this, &CommunicationService::onLinkStatusChanged);
    connect(d->commWorker, &CommunicatorWorker::linkStatisticsChanged,
            this, &CommunicationService::onLinkStatisticsChanged);
    connect(d->commWorker, &CommunicatorWorker::mavLinkStatisticsChanged,
            this, &CommunicationService::onMavLinkStatisticsChanged);
    connect(d->commWorker, &CommunicatorWorker::mavLinkProtocolChanged,
            this, &CommunicationService::onMavlinkProtocolChanged);

    d->loadDescriptions();
}

CommunicationService::~CommunicationService()
{
    for (const dao::LinkDescriptionPtr& description: this->descriptions())
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

dao::LinkDescriptionPtr CommunicationService::description(int id) const
{
    return d->linkRepository.read(id);
}

dao::LinkDescriptionPtrList CommunicationService::descriptions()
{
    return d->linkRepository.loadedEntities();
}

void CommunicationService::init()
{
    // TODO: different link protocols
    comm::MavLinkCommunicatorFactory commFactory(
                settings::Provider::value(settings::communication::systemId).toInt(),
                settings::Provider::value(settings::communication::componentId).toInt());
    comm::AbstractCommunicator* communicator = commFactory.create();

    d->commWorker->setCommunicator(communicator);
    d->commThread->start();

    for (const dao::LinkDescriptionPtr& description: this->descriptions())
    {
        comm::LinkFactoryPtr factory(new comm::DescriptionLinkFactory(
                                         description));
        d->commWorker->updateLink(description->id(),
                                  factory, description->isAutoConnect());

        if (description->type() == dao::LinkDescription::Serial &&
            !description->device().isEmpty())
        {
            d->serialPortService->holdDevice(description->device());
            d->descriptedDevices[description] = description->device();
        }
    }
}

bool CommunicationService::save(const dao::LinkDescriptionPtr& description)
{
    bool isNew = description->id() == 0;
    if (!d->linkRepository.save(description)) return false;

    comm::LinkFactoryPtr factory(new comm::DescriptionLinkFactory(
                                     description));
    d->commWorker->updateLink(description->id(),
                              factory, description->isAutoConnect());

    if (d->descriptedDevices.contains(description) &&
        description->device() != d->descriptedDevices[description])
    {
        d->serialPortService->releaseDevice(d->descriptedDevices.take(description));
    }

    isNew ? descriptionAdded(description) : descriptionChanged(description);

    if (description->type() == dao::LinkDescription::Serial &&
        !description->device().isEmpty() && !d->descriptedDevices.contains(description))
    {
        d->serialPortService->holdDevice(description->device());
        d->descriptedDevices[description] = description->device();
    }

    return true;
}

bool CommunicationService::remove(const dao::LinkDescriptionPtr& description)
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

void CommunicationService::setLinkConnected(const dao::LinkDescriptionPtr& description,
                                            bool connected)
{
    d->commWorker->setLinkConnected(description->id(), connected);

    description->setAutoConnect(connected);
}

void CommunicationService::onLinkStatusChanged(int linkId, bool connected)
{
    dao::LinkDescriptionPtr description = this->description(linkId);

    if (description->isConnected() != connected)
    {
        LogBus::log(tr("Link") + " " + description->name() + " " +
                    (connected ? tr("connected") : tr("disconnected")),
                    connected ? LogMessage::Positive : LogMessage::Warning);
        description->setConnected(connected);

        emit linkStatusChanged(description);
    }
}

void CommunicationService::onLinkStatisticsChanged(int linkId,
                                                   int timestamp,
                                                   int bytesReceivedSec,
                                                   int bytesSentSec)
{
    dao::LinkStatisticsPtr statistics = d->getlinkStatistics(linkId);

    statistics->setTimestamp(timestamp);
    statistics->setBytesRecv(bytesReceivedSec);
    statistics->setBytesSent(bytesSentSec);

    emit linkStatisticsChanged(statistics);
}

void CommunicationService::onMavLinkStatisticsChanged(int linkId,
                                                      int packetsReceived,
                                                      int packetsDrops)
{
    dao::LinkStatisticsPtr statistics = d->getlinkStatistics(linkId);

    statistics->setPacketsRecv(packetsReceived);
    statistics->setPacketDrops(packetsDrops);

    // TODO: No handle for MavLinkStatistics yet
}

void CommunicationService::onMavlinkProtocolChanged(int linkId,
                                                    dao::LinkDescription::Protocol protocol)
{
    dao::LinkDescriptionPtr description = this->description(linkId);
    if (description->protocol() == protocol) return;

    QString msg;
    if (protocol == dao::LinkDescription::MavLink1) msg = tr("switched on MAVLINK v.1");
    if (protocol == dao::LinkDescription::MavLink2) msg = tr("switched on MAVLINK v.2");

    LogBus::log(tr("Link") + " " + description->name() + " " + msg);
    description->setProtocol(protocol);

    emit linkStatusChanged(description);
}

void CommunicationService::onDevicesChanged()
{
    QStringList devices = d->serialPortService->devices();

    for (const dao::LinkDescriptionPtr& description: d->descriptedDevices.keys())
    {
        if (!description->isConnected() && description->isAutoConnect() &&
            devices.contains(description->device()))
        {
            this->setLinkConnected(description, true);
        }
    }
}
