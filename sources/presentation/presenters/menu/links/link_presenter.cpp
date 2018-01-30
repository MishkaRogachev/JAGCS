#include "link_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "link_description.h"
#include "link_statistics.h"

#include "service_registry.h"
#include "serial_ports_service.h"
#include "communication_service.h"

#include "link_statistics_model.h"

using namespace presentation;

class LinkPresenter::Impl
{
public:
    dao::LinkDescriptionPtr description;

    domain::SerialPortService* const serialService =
            domain::ServiceRegistry::serialPortService();
    domain::CommunicationService* const commService =
            domain::ServiceRegistry::communicationService();

    LinkStatisticsModel model;
};

LinkPresenter::LinkPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    connect(d->serialService, &domain::SerialPortService::availableDevicesChanged,
            this, &LinkPresenter::updateDevices);

    connect(d->commService, &domain::CommunicationService::descriptionChanged, this,
            [this](const dao::LinkDescriptionPtr& description) {
        if (d->description == description) this->updateLink();
    });
    connect(d->commService, &domain::CommunicationService::linkStatusChanged, this,
            [this](const dao::LinkDescriptionPtr& description) {
        if (d->description == description) this->updateStatus();
    });
    connect(d->commService, &domain::CommunicationService::linkStatisticsChanged, this,
            [this](const dao::LinkStatisticsPtr& statistics) {
        if (d->description->id() != statistics->linkId()) return;

        //d->model.addData(statistics->bytesRecv(), statistics->bytesSent());
    });
}

LinkPresenter::~LinkPresenter()
{}

void LinkPresenter::setLink(int id)
{
    d->description = d->commService->description(id);

    this->updateDevices();
    this->updateLink();
    this->updateStatus();
}

void LinkPresenter::updateRates()
{
    QVariantList baudRates;
    for (qint32 rate: domain::SerialPortService::availableBaudRates()) baudRates.append(rate);
    this->setViewProperty(PROPERTY(baudRates), baudRates);
}

void LinkPresenter::updateLink()
{
    this->setViewProperty(PROPERTY(type), d->description ? d->description->type() :
                                                           dao::LinkDescription::UnknownType);
    this->setViewProperty(PROPERTY(name), d->description ? d->description->name() : QString());
    this->setViewProperty(PROPERTY(port), d->description ? d->description->port() : 0);
    this->setViewProperty(PROPERTY(device), d->description ? d->description->device() : QString());
    this->setViewProperty(PROPERTY(baudRate), d->description ? d->description->baudRate() : 0);

    this->setViewProperty(PROPERTY(changed), false);
}

void LinkPresenter::updateStatus()
{
    this->setViewProperty(PROPERTY(connected), d->description &&
                          d->description->isConnected());
    this->setViewProperty(PROPERTY(protocol), d->description ?
                              d->description->protocol() :
                              dao::LinkDescription::UnknownProtocol);
}

void LinkPresenter::updateDevices()
{
    QStringList devices;
    devices.append(QString());

    for (const QString& device: d->serialService->availableDevices())
    {
        devices.append(device);
    }

    if (d->description && !devices.contains(d->description->device()))
    {
        devices.append(d->description->device());
    }

    this->setViewProperty(PROPERTY(devices), devices);
}

void LinkPresenter::setConnected(bool connected)
{
    if (d->description.isNull()) return;

    d->commService->setLinkConnected(d->description, connected);
}

void LinkPresenter::save()
{
    if (d->description.isNull()) return;

    d->description->setName(this->viewProperty(PROPERTY(name)).toString());
    d->description->setPort(this->viewProperty(PROPERTY(port)).toInt());
    d->description->setDevice(this->viewProperty(PROPERTY(device)).toString());
    d->description->setBaudRate(this->viewProperty(PROPERTY(baudRate)).toInt());

    if (!d->commService->save(d->description)) return;

    this->setViewProperty(PROPERTY(changed), false);
}

void LinkPresenter::remove()
{
    if (d->description.isNull()) return;

    d->commService->remove(d->description);
}

void LinkPresenter::connectView(QObject* view)
{
    view->setProperty(PROPERTY(statistics), QVariant::fromValue(&d->model));
}
