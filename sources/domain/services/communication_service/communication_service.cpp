#include "communication_service.h"

// Qt
#include <QThread>
#include <QMap>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "link_description.h"
#include "generic_repository.h"
#include "generic_repository_impl.h"

#include "serial_ports_service.h"

#include "mavlink_communicator_factory.h"
#include "communicator_worker.h"

using namespace domain;

class CommunicationService::Impl
{
public:
    SerialPortService* serialPortService;
    QMap<dao::LinkDescriptionPtr, QString> descriptionDevices;

    QThread* commThread;
    CommunicatorWorker* commWorker;

    GenericRepository<dao::LinkDescription> linkRepository;

    Impl():
        linkRepository("links")
    {}
};

CommunicationService::CommunicationService(SerialPortService* serialPortService, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    qRegisterMetaType<dao::LinkDescriptionPtr>("dao::LinkDescriptionPtr");
    qRegisterMetaType<dao::LinkDescription::Protocol>("dao::LinkDescription::Protocol");
    qRegisterMetaType<comm::AbstractCommunicator::Protocol>("comm::AbstractCommunicator::Protocol");

    d->serialPortService = serialPortService;

    d->commThread = new QThread(this);
    d->commThread->setObjectName("Communication thread");

    d->commWorker = new CommunicatorWorker();

    connect(d->commThread, &QThread::finished, d->commWorker, &QObject::deleteLater);
    connect(d->commWorker, &CommunicatorWorker::linkStatisticsChanged,
            this, &CommunicationService::onLinkStatisticsChanged);
    connect(d->commWorker, &CommunicatorWorker::mavLinkStatisticsChanged,
            this, &CommunicationService::onMavLinkStatisticsChanged);
    connect(d->commWorker, &CommunicatorWorker::mavLinkProtocolChanged,
            this, &CommunicationService::onMavlinkProtocolChanged);
}

CommunicationService::~CommunicationService()
{
    for (const dao::LinkDescriptionPtr& description: this->descriptions())
    {
        description->setAutoConnect(description->isConnected());
        this->save(description);

        if (d->descriptionDevices.contains(description))
        {
            d->serialPortService->releaseDevice(d->descriptionDevices.take(description));
        }
    }

    d->commThread->quit();
    d->commThread->wait();
}

dao::LinkDescriptionPtr CommunicationService::description(int id, bool reload)
{
    return d->linkRepository.read(id, reload);
}

dao::LinkDescriptionPtrList CommunicationService::descriptions(const QString& condition, bool reload)
{
    dao::LinkDescriptionPtrList list;

    for (int id: d->linkRepository.selectId(condition))
    {
        list.append(this->description(id, reload));
    }

    return list;
}

void CommunicationService::init()
{
    // TODO: different link protocols
    comm::MavLinkCommunicatorFactory commFactory(
                settings::Provider::value(settings::communication::systemId).toInt(),
                settings::Provider::value(settings::communication::componentId).toInt());

    d->commWorker->initCommunicator(&commFactory);
    d->commWorker->moveToThread(d->commThread);
    d->commThread->start();

    for (const dao::LinkDescriptionPtr& description: this->descriptions())
    {
        QMetaObject::invokeMethod(d->commWorker, "updateLinkFromDescription",
                                  Qt::QueuedConnection, Q_ARG(dao::LinkDescriptionPtr, description));

        if (description->type() == dao::LinkDescription::Serial &&
            !description->device().isEmpty())
        {
            d->serialPortService->holdDevice(description->device());
            d->descriptionDevices[description] = description->device();
        }
    }
}

bool CommunicationService::save(const dao::LinkDescriptionPtr& description)
{
    bool isNew = description->id() == 0;
    if (!d->linkRepository.save(description)) return false;

    QMetaObject::invokeMethod(d->commWorker, "updateLinkFromDescription",
                              Qt::QueuedConnection, Q_ARG(dao::LinkDescriptionPtr, description));

    if (d->descriptionDevices.contains(description) &&
        description->device() != d->descriptionDevices[description])
    {
        d->serialPortService->releaseDevice(d->descriptionDevices.take(description));
    }

    isNew ? descriptionAdded(description) : descriptionChanged(description);

    if (description->type() == dao::LinkDescription::Serial &&
        !description->device().isEmpty() && !d->descriptionDevices.contains(description))
    {
        d->serialPortService->holdDevice(description->device());
        d->descriptionDevices[description] = description->device();
    }

    return true;
}

bool CommunicationService::remove(const dao::LinkDescriptionPtr& description)
{
    if (!d->linkRepository.remove(description)) return false;

    QMetaObject::invokeMethod(d->commWorker, "removeLinkByDescription",
                              Qt::QueuedConnection, Q_ARG(dao::LinkDescriptionPtr, description));

    if (d->descriptionDevices.contains(description))
    {
        d->serialPortService->releaseDevice(d->descriptionDevices.take(description));
    }

    emit descriptionRemoved(description);

    return true;
}

void CommunicationService::setLinkConnected(const dao::LinkDescriptionPtr& description,
                                            bool connected)
{
    QMetaObject::invokeMethod(d->commWorker, "setLinkConnected",
                              Qt::QueuedConnection,
                              Q_ARG(dao::LinkDescriptionPtr, description),
                              Q_ARG(bool, connected));
}

void CommunicationService::onLinkStatisticsChanged(const dao::LinkDescriptionPtr& description,
                                                   int bytesReceivedSec,
                                                   int bytesSentSec,
                                                   bool connected)
{
    description->addBytesRecv(bytesReceivedSec);
    description->addBytesSent(bytesSentSec);
    description->setConnected(connected);

    emit linkStatisticsChanged(description);
}

void CommunicationService::onMavLinkStatisticsChanged(const dao::LinkDescriptionPtr& description,
                                                      int packetsReceived, int packetsDrops)
{
    description->addPacketsRecv(packetsReceived);
    description->addPacketDrops(packetsDrops);

    emit linkStatisticsChanged(description);
}

void CommunicationService::onMavlinkProtocolChanged(const dao::LinkDescriptionPtr& description,
                                                    dao::LinkDescription::Protocol protocol)
{
    description->setProtocol(protocol);

    emit linkStatisticsChanged(description);
}
