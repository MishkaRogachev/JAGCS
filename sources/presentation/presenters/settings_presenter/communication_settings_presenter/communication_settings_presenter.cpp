#include "communication_settings_presenter.h"

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "domain_entry.h"

#include "db_facade.h"
#include "link_description.h"

#include "settings_provider.h"
#include "communication_service.h"

#include "communication_link_presenter.h"

using namespace presentation;
using namespace domain;

class CommunicationSettingsPresenter::Impl
{
public:
    db::DbFacade* dbFacade;
    domain::CommunicationService* service;

    QMap<dao::LinkDescriptionPtr, CommunicationLinkPresenter*> linkPresenters;
};

CommunicationSettingsPresenter::CommunicationSettingsPresenter(domain::DomainEntry* entry,
                                                               QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->dbFacade = entry->dbFacade();
    d->service = entry->commService();

    connect(d->dbFacade, &dao::DbFacade::linkAdded,
            this, &CommunicationSettingsPresenter::onLinkAdded);
    connect(d->dbFacade, &dao::DbFacade::linkChanged,
            this, &CommunicationSettingsPresenter::onLinkChanged);
    connect(d->dbFacade, &dao::DbFacade::linkRemoved,
            this, &CommunicationSettingsPresenter::onLinkRemoved);
    connect(d->service, &CommunicationService::linkStatisticsChanged,
            this, &CommunicationSettingsPresenter::onLinkStatisticsChanged);

    for (const dao::LinkDescriptionPtr& description: d->dbFacade->links())
    {
        d->linkPresenters[description] =
                new CommunicationLinkPresenter(d->dbFacade, d->service, description, this);
    }
}

CommunicationSettingsPresenter::~CommunicationSettingsPresenter()
{}

void CommunicationSettingsPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(addUdpLink()), this, SLOT(onAddUdpLink()));
    connect(view, SIGNAL(addSerialLink()), this, SLOT(onAddSerialLink()));

    this->updateCommunicationsLinks();
}

void CommunicationSettingsPresenter::onLinkAdded(
        const dao::LinkDescriptionPtr& description)
{
    d->linkPresenters[description] =
            new CommunicationLinkPresenter(d->dbFacade, d->service, description, this);

    this->updateCommunicationsLinks();
}

void CommunicationSettingsPresenter::onLinkChanged(
        const dao::LinkDescriptionPtr& description)
{
    if (!d->linkPresenters.contains(description)) return;
    d->linkPresenters[description]->updateView();
}

void CommunicationSettingsPresenter::onLinkStatisticsChanged(
        const dao::LinkDescriptionPtr& description)
{
    if (!d->linkPresenters.contains(description)) return;
    d->linkPresenters[description]->updateStatistics();
}

void CommunicationSettingsPresenter::onLinkRemoved(
        const dao::LinkDescriptionPtr& description)
{
    if (!d->linkPresenters.contains(description)) return;
    CommunicationLinkPresenter* linkPresenter = d->linkPresenters.take(description);

    delete linkPresenter;
    this->updateCommunicationsLinks();
}

void CommunicationSettingsPresenter::updateCommunicationsLinks()
{
    QList<QObject*> objectList;
    for (CommunicationLinkPresenter* linkPresenter: d->linkPresenters.values())
    {
        objectList.append(linkPresenter);
    }

    this->setViewProperty(PROPERTY(links), QVariant::fromValue(objectList));
}

void CommunicationSettingsPresenter::onAddUdpLink()
{
    auto description = dao::LinkDescriptionPtr::create();

    description->setName(tr("New UDP Link"));
    description->setType(dao::LinkDescription::Udp);
    description->setPort(settings::Provider::value(settings::communication::port).toInt());

    d->dbFacade->save(description);
}

void CommunicationSettingsPresenter::onAddSerialLink()
{
    auto description = dao::LinkDescriptionPtr::create();

    description->setName(tr("New Serial Link"));
    description->setType(dao::LinkDescription::Serial);
    description->setBaudRate(settings::Provider::value(settings::communication::baudRate).toInt());

    d->dbFacade->save(description);
}
