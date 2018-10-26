#include "link_list_vm.h"

// Qt
#include <QSortFilterProxyModel>
#include <QVariant>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "communication_link.h"

#include "service_registry.h"
#include "communication_service.h"

#include "link_list_model.h"

using namespace presentation;

class LinkListVm::Impl
{
public:
    domain::CommunicationService* const service = serviceRegistry->communicationService();

    LinkListModel linksModel;
    QSortFilterProxyModel filterModel;
};

LinkListVm::LinkListVm(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->filterModel.setSourceModel(&d->linksModel);
    d->filterModel.setFilterRole(LinkListModel::LinkNameRole);
    d->filterModel.setSortRole(LinkListModel::LinkNameRole);
    d->filterModel.setDynamicSortFilter(true);
    d->filterModel.sort(0, Qt::AscendingOrder);

    d->linksModel.setLinks(d->service->descriptions());

    connect(d->service, &domain::CommunicationService::linkAdded,
            &d->linksModel, &LinkListModel::addLink);
    connect(d->service, &domain::CommunicationService::linkRemoved,
            &d->linksModel, &LinkListModel::removeLink);
    connect(d->service, &domain::CommunicationService::descriptionChanged,
            &d->linksModel, &LinkListModel::updateLink);
}

LinkListVm::~LinkListVm()
{}

QAbstractItemModel* LinkListVm::links() const
{
    return &d->filterModel;
}

void LinkListVm::filter(const QString& filterString)
{
    d->filterModel.setFilterFixedString(filterString);
}

void LinkListVm::addLink(data_source::LinkDescription::Type type, const QString& name)
{
    data_source::LinkDescriptionPtr description = data_source::LinkDescriptionPtr::create();

    description->setType(type);
    description->setName(name + " " + tr("link"));
    description->setAutoConnect(true);

    QStringList availableProtocols = d->service->availableProtocols();
    if (!availableProtocols.isEmpty()) description->setProtocol(availableProtocols.first());

    switch (type) {
    case data_source::LinkDescription::Serial:
        description->setParameter(data_source::LinkDescription::BaudRate,
                                  settings::Provider::value(settings::communication::baudRate));
        break;
    case data_source::LinkDescription::Udp:
        description->setParameter(data_source::LinkDescription::Port,
                                  settings::Provider::value(settings::communication::udpPort));
        description->setParameter(data_source::LinkDescription::UdpAutoResponse, true);
        break;
    case data_source::LinkDescription::Tcp:
        description->setParameter(data_source::LinkDescription::Address,
                                  settings::Provider::value(settings::communication::tcpAddress));
        description->setParameter(data_source::LinkDescription::Port,
                                  settings::Provider::value(settings::communication::tcpPort));
        break;
    case data_source::LinkDescription::Bluetooth:
        description->setParameter(data_source::LinkDescription::Address,
                                  settings::Provider::value(settings::communication::bluetoothAddress));
        d->service->save(description);
        break;
    default:
        break;
    }

    d->service->save(description);
}

void LinkListVm::removeLink(const data_source::LinkDescriptionPtr& description)
{
    d->service->remove(description);
}
