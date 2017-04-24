#include "communications_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "link_description.h"

#include "settings_provider.h"
#include "communication_manager.h"

#include "communication_link_presenter.h"

using namespace presentation;
using namespace domain;

class CommunicationsPresenter::Impl
{
public:
    domain::CommunicationManager* manager;

    QList<CommunicationLinkPresenter*> linkPresenters;
};

CommunicationsPresenter::CommunicationsPresenter(
        domain::CommunicationManager* manager,
        QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->manager = manager;

    connect(manager, &CommunicationManager::linkAdded,
            this, &CommunicationsPresenter::onLinkAdded);
    connect(manager, &CommunicationManager::linkRemoved,
            this, &CommunicationsPresenter::onLinkRemoved);

    for (const db::LinkDescriptionPtr& description: manager->links())
    {
        d->linkPresenters.append(new CommunicationLinkPresenter(
                                     d->manager, description, this));
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
                                 d->manager, description, this));

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

    d->manager->saveLink(description);
}

void CommunicationsPresenter::onAddSerialLink()
{
    auto description = db::LinkDescriptionPtr::create();

    description->setName(tr("New Serial Link"));
    description->setType(db::LinkDescription::Serial);
    description->setBaudRate(domain::SettingsProvider::value(
                            settings::communication::baudRate).toInt());

    d->manager->saveLink(description);
}
