#include "communications_presenter.h"

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
    // TODO:
}

void CommunicationsPresenter::onAddUdpLink()
{
    auto description = data_source::LinkDescriptionPtr::create();

    description->setType(data_source::LinkDescription::Udp);
    description->setPort(domain::SettingsProvider::value(
                            settings::communication::port).toInt());

    d->manager->addLink(description);
}

void CommunicationsPresenter::onAddSerialLink()
{
    auto description = data_source::LinkDescriptionPtr::create();

    description->setType(data_source::LinkDescription::Serial);
    description->setBaudRate(domain::SettingsProvider::value(
                            settings::communication::baudRate).toInt());

    d->manager->addLink(description);
}

