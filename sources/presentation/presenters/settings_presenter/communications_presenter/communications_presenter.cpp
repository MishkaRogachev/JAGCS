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

    connect(manager, &CommunicationManager::linksChanged,
            this, &CommunicationsPresenter::updateCommunicationsLinks);
}

CommunicationsPresenter::~CommunicationsPresenter()
{}

void CommunicationsPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(addUdpLink()), this, SLOT(onAddUdpLink()));
    connect(view, SIGNAL(addSerialLink()), this, SLOT(onAddSerialLink()));

    this->updateCommunicationsLinks();
}

void CommunicationsPresenter::updateCommunicationsLinks()
{
    data_source::LinkDescriptionPtrList links = d->manager->links();

    for (CommunicationLinkPresenter* linkPresenter: d->linkPresenters)
    {
        if (links.contains(linkPresenter->description()))
        {
            links.removeOne(linkPresenter->description());
            continue;
        }

        d->linkPresenters.removeOne(linkPresenter);
        linkPresenter->deleteLater();
    }

    for (const data_source::LinkDescriptionPtr& description: links)
    {
        d->linkPresenters.append(new CommunicationLinkPresenter(description,
                                                                this));
    }

    this->setViewProperty(PROPERTY(links), d->linkPresenters.count());
}

void CommunicationsPresenter::onAddUdpLink()
{
    auto description = data_source::LinkDescriptionPtr::create();

    description->setType(data_source::LinkDescription::Udp);
    description->setPort(domain::SettingsProvider::value(
                            settings::communication::port).toInt());

    d->manager->saveLink(description);
}

void CommunicationsPresenter::onAddSerialLink()
{
    auto description = data_source::LinkDescriptionPtr::create();

    description->setType(data_source::LinkDescription::Serial);
    description->setBaudRate(domain::SettingsProvider::value(
                            settings::communication::baudRate).toInt());

    d->manager->saveLink(description);
}

