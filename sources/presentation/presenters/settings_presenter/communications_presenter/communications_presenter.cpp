#include "communications_presenter.h"

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

class CommunicationsPresenter::Impl
{
public:
    db::DbFacade* dbFacade;
    domain::CommunicationService* service;

    QMap<db::LinkDescriptionPtr, CommunicationLinkPresenter*> linkPresenters;
};

CommunicationsPresenter::CommunicationsPresenter(domain::DomainEntry* entry,
                                                 QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->dbFacade = entry->dbFacade();
    d->service = entry->commService();

    connect(d->dbFacade, &db::DbFacade::linkAdded,
            this, &CommunicationsPresenter::onLinkAdded);
    connect(d->dbFacade, &db::DbFacade::linkChanged,
            this, &CommunicationsPresenter::onLinkChanged);
    connect(d->dbFacade, &db::DbFacade::linkRemoved,
            this, &CommunicationsPresenter::onLinkRemoved);
    connect(d->service, &CommunicationService::linkStatisticsChanged,
            this, &CommunicationsPresenter::onLinkStatisticsChanged);

    for (const db::LinkDescriptionPtr& description: d->dbFacade->links())
    {
        d->linkPresenters[description] =
                new CommunicationLinkPresenter(d->dbFacade, d->service, description, this);
    }
}

CommunicationsPresenter::~CommunicationsPresenter()
{}

void CommunicationsPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(addUdpLink()), this, SLOT(onAddUdpLink()));
    connect(view, SIGNAL(addSerialLink()), this, SLOT(onAddSerialLink()));

    this->updateCommunicationsLinks();
}

void CommunicationsPresenter::onLinkAdded(
        const db::LinkDescriptionPtr& description)
{
    d->linkPresenters[description] =
            new CommunicationLinkPresenter(d->dbFacade, d->service, description, this);

    this->updateCommunicationsLinks();
}

void CommunicationsPresenter::onLinkChanged(const db::LinkDescriptionPtr& description)
{
    if (!d->linkPresenters.contains(description)) return;
    d->linkPresenters[description]->updateView();
}

void CommunicationsPresenter::onLinkStatisticsChanged(const db::LinkDescriptionPtr& description)
{
    if (!d->linkPresenters.contains(description)) return;
    d->linkPresenters[description]->updateStatistics();
}

void CommunicationsPresenter::onLinkRemoved(
        const db::LinkDescriptionPtr& description)
{
    if (!d->linkPresenters.contains(description)) return;
    CommunicationLinkPresenter* linkPresenter = d->linkPresenters.take(description);

    delete linkPresenter;
    this->updateCommunicationsLinks();
}

void CommunicationsPresenter::updateCommunicationsLinks()
{
    QList<QObject*> objectList;
    for (CommunicationLinkPresenter* linkPresenter: d->linkPresenters.values())
    {
        objectList.append(linkPresenter);
    }

    this->setViewProperty(PROPERTY(links), QVariant::fromValue(objectList));
}

void CommunicationsPresenter::onAddUdpLink()
{
    auto description = db::LinkDescriptionPtr::create();

    description->setName(tr("New UDP Link"));
    description->setType(db::LinkDescription::Udp);
    description->setPort(domain::SettingsProvider::value(
                            settings::communication::port).toInt());

    d->dbFacade->save(description);
}

void CommunicationsPresenter::onAddSerialLink()
{
    auto description = db::LinkDescriptionPtr::create();

    description->setName(tr("New Serial Link"));
    description->setType(db::LinkDescription::Serial);
    description->setBaudRate(domain::SettingsProvider::value(
                            settings::communication::baudRate).toInt());

    d->dbFacade->save(description);
}
