#include "communications_presenter.h"

// Internal
#include "settings_provider.h"

#include "udp_link.h"
#include "serial_link.h"

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
}

void CommunicationsPresenter::updateCommunicationsLinks()
{
    QList<QObject*> list; // TODO: list

    this->setViewProperty(PROPERTY(commLinks), QVariant::fromValue(list));
}

void CommunicationsPresenter::onAddUdpLink()
{
    d->manager->addLink(new data_source::UdpLink(SettingsProvider::value(
                                        settings::communication::port).toInt()));
}

void CommunicationsPresenter::onAddSerialLink()
{
    d->manager->addLink(new data_source::SerialLink(SettingsProvider::value(
                              settings::communication::serialDevice).toString(),
                                                    SettingsProvider::value(
                              settings::communication::baudRate).toInt()));
}

