#include "link_list_provider.h"

// Qt
#include <QSortFilterProxyModel>
#include <QVariant>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "link_description.h"

#include "service_registry.h"
#include "communication_service.h"

#include "object_list_model.h"
#include "link_provider.h"

using namespace presentation;

class LinkListProvider::Impl
{
public:
    domain::CommunicationService* const service = serviceRegistry->communicationService();

    QMap<dto::LinkDescriptionPtr, LinkProvider*> descriptedPresenters;
    ObjectListModel<LinkProvider> linksModel;
    QSortFilterProxyModel filterModel;
};

LinkListProvider::LinkListProvider(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->filterModel.setSourceModel(&d->linksModel);
/*    d->filterModel.setFilterRole(LinkListModel::LinkNameRole);
    d->filterModel.setSortRole(LinkListModel::LinkNameRole);
    d->filterModel.setDynamicSortFilter(true);
    d->filterModel.sort(0, Qt::AscendingOrder);*/

    for (const dto::LinkDescriptionPtr& description: d->service->descriptions())
    {
        this->onDescriptionAdded(description);
    }

    connect(d->service, &domain::CommunicationService::descriptionAdded,
            this, &LinkListProvider::onDescriptionAdded);
    connect(d->service, &domain::CommunicationService::descriptionRemoved,
            this, &LinkListProvider::onDescriptionRemoved);
}

LinkListProvider::~LinkListProvider()
{}

QAbstractItemModel* LinkListProvider::links() const
{
    return &d->filterModel;
}

void LinkListProvider::addSerialLink()
{
    dto::LinkDescriptionPtr description = dto::LinkDescriptionPtr::create();

    description->setName(tr("Serial Link"));
    description->setType(dto::LinkDescription::Serial);
    description->setParameter(dto::LinkDescription::BaudRate,
                              settings::Provider::value(settings::communication::baudRate));

    d->service->save(description);
}

void LinkListProvider::addUdpLink()
{
    dto::LinkDescriptionPtr description = dto::LinkDescriptionPtr::create();

    description->setName(tr("UDP Link"));
    description->setType(dto::LinkDescription::Udp);
    description->setParameter(dto::LinkDescription::Port,
                              settings::Provider::value(settings::communication::udpPort));
    description->setParameter(dto::LinkDescription::UdpAutoResponse, true);

    d->service->save(description);
}

void LinkListProvider::addTcpLink()
{
    dto::LinkDescriptionPtr description = dto::LinkDescriptionPtr::create();

    description->setName(tr("TCP Link"));
    description->setType(dto::LinkDescription::Tcp);
    description->setParameter(dto::LinkDescription::Address,
                              settings::Provider::value(settings::communication::tcpAddress));
    description->setParameter(dto::LinkDescription::Port,
                              settings::Provider::value(settings::communication::tcpPort));

    d->service->save(description);
}

void LinkListProvider::addBluetoothLink()
{
    dto::LinkDescriptionPtr description = dto::LinkDescriptionPtr::create();

    description->setName(tr("Bluetooth"));
    description->setType(dto::LinkDescription::Bluetooth);
    description->setParameter(dto::LinkDescription::Address,
                              settings::Provider::value(settings::communication::bluetoothAddress));

    d->service->save(description);
}

void LinkListProvider::filter(const QString& filterString)
{
    d->filterModel.setFilterFixedString(filterString);
}

void LinkListProvider::onDescriptionAdded(const dto::LinkDescriptionPtr& description)
{
    LinkProvider* presenter = new LinkProvider(description, this);

    d->descriptedPresenters[description] = presenter;
    d->linksModel.append(presenter);
}

void LinkListProvider::onDescriptionRemoved(const dto::LinkDescriptionPtr& description)
{
    LinkProvider* presenter = d->descriptedPresenters.take(description);
    if (!presenter) return;

    d->linksModel.remove(presenter);
    delete presenter;
}
