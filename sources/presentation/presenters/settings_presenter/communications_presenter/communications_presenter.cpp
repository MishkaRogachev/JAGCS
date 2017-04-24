#include "communications_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "link_description.h"

#include "settings_provider.h"
#include "communication_service.h"

#include "communication_link_presenter.h"

using namespace presentation;
using namespace domain;

class CommunicationsPresenter::Impl
{
public:
    domain::CommunicationService* service;

    QList<CommunicationLinkPresenter*> linkPresenters;
};

CommunicationsPresenter::CommunicationsPresenter(
        domain::CommunicationService* service,
        QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->service = service;

    connect(manager, &CommunicationService::linkAdded,
            this, &CommunicationsPresenter::onLinkAdded);
    connect(manager, &CommunicationService::linkRemoved,
            this, &CommunicationsPresenter::onLinkRemoved);

    for (const db::LinkDescriptionPtr& description: service->links())
    {
        d->linkPresenters.append(new CommunicationLinkPresenter(
                                     d->service, description, this));
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
    d->linkPresenters.append(new CommunicationLinkPresenter(
                                 d->service, description, this));

    this->updateCommunicationsLinks();
}

void CommunicationsPresenter::onLinkRemoved(
        const db::LinkDescriptionPtr& description)
{
    for (CommunicationLinkPresenter* linkPresenter: d->linkPresenters)
    {
        if (linkPresenter->description() != description) continue;

        d->linkPresenters.removeOne(linkPresenter);
        delete linkPresenter;
        this->updateCommunicationsLinks();
        return;
    }
}

void CommunicationsPresenter::updateCommunicationsLinks()
{
    QList<QObject*> objectList;
    for (CommunicationLinkPresenter* linkPresenter: d->linkPresenters)
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

    d->service->saveLink(description);
}

void CommunicationsPresenter::onAddSerialLink()
{
    auto description = db::LinkDescriptionPtr::create();

    description->setName(tr("New Serial Link"));
    description->setType(db::LinkDescription::Serial);
    description->setBaudRate(domain::SettingsProvider::value(
                            settings::communication::baudRate).toInt());

    d->service->saveLink(description);
}
