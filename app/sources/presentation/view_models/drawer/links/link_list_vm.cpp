#include "link_list_vm.h"

// Qt
#include <QSortFilterProxyModel>
#include <QVariant>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "link_description.h"

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

    connect(d->service, &domain::CommunicationService::descriptionAdded,
            &d->linksModel, &LinkListModel::addLink);
    connect(d->service, &domain::CommunicationService::descriptionRemoved,
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

void LinkListVm::addLink(dto::LinkDescription::Type type)
{
    dto::LinkDescriptionPtr description = dto::LinkDescriptionPtr::create();

    description->setType(type);
    description->setName(tr("Link %1").arg(d->linksModel.rowCount() + 1));

    switch (type) {
    case dto::LinkDescription::Serial:
        description->setParameter(dto::LinkDescription::BaudRate,
                                  settings::Provider::value(settings::communication::baudRate));
        break;
    case dto::LinkDescription::Udp:
        description->setParameter(dto::LinkDescription::Port,
                                  settings::Provider::value(settings::communication::udpPort));
        description->setParameter(dto::LinkDescription::UdpAutoResponse, true);
        break;
    case dto::LinkDescription::Tcp:
        description->setParameter(dto::LinkDescription::Address,
                                  settings::Provider::value(settings::communication::tcpAddress));
        description->setParameter(dto::LinkDescription::Port,
                                  settings::Provider::value(settings::communication::tcpPort));
        break;
    case dto::LinkDescription::Bluetooth:
        description->setParameter(dto::LinkDescription::Address,
                                  settings::Provider::value(settings::communication::bluetoothAddress));
        d->service->save(description);
        break;
    default:
        break;
    }

    d->service->save(description);
}

void LinkListVm::removeLink(const dto::LinkDescriptionPtr& description)
{
    d->service->remove(description);
}
