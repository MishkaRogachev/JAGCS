#include "communication_service.h"

// Qt
#include <QThread>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "link_description.h"
#include "generic_repository.h"
#include "generic_repository_impl.h"

#include "mavlink_communicator_factory.h"
#include "communicator_worker.h"

using namespace domain;

class CommunicationService::Impl
{
public:
    QThread* commThread;
    CommunicatorWorker* commWorker;

    GenericRepository<dao::LinkDescription> linkRepository;

    Impl():
        linkRepository("links")
    {}
};

CommunicationService::CommunicationService(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    qRegisterMetaType<dao::LinkDescriptionPtr>("dao::LinkDescriptionPtr");

    d->commThread = new QThread(this);
    d->commThread->setObjectName("Communication thread");

    d->commWorker = new CommunicatorWorker();

    connect(d->commThread, &QThread::finished, d->commWorker, &QObject::deleteLater);
    connect(d->commWorker, &CommunicatorWorker::linkStatisticsChanged,
            this, &CommunicationService::onLinkStatisticsChanged);
}

CommunicationService::~CommunicationService()
{
    for (const dao::LinkDescriptionPtr& description: this->descriptions())
    {
        description->setAutoConnect(description->isConnected());
        this->save(description);
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
    }
}

bool CommunicationService::save(const dao::LinkDescriptionPtr& description)
{
    bool isNew = description->id() == 0;
    if (!d->linkRepository.save(description)) return false;

    isNew ? descriptionAdded(description) : descriptionChanged(description);
    QMetaObject::invokeMethod(d->commWorker, "updateLinkFromDescription",
                              Qt::QueuedConnection, Q_ARG(dao::LinkDescriptionPtr, description));

    return true;
}

bool CommunicationService::remove(const dao::LinkDescriptionPtr& description)
{
    if (!d->linkRepository.remove(description)) return false;

    QMetaObject::invokeMethod(d->commWorker, "removeLinkByDescription",
                              Qt::QueuedConnection, Q_ARG(dao::LinkDescriptionPtr, description));
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
    description->setBytesRecvSec(bytesReceivedSec);
    description->setBytesSentSec(bytesSentSec);
    description->setConnected(connected);

    emit linkStatisticsChanged(description);
}
