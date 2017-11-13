#include "communications_presenter.h"

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "service_registry.h"

#include "communication_service.h"
#include "link_description.h"

#include "communication_link_presenter.h"

using namespace presentation;
using namespace domain;

class CommunicationsPresenter::Impl
{
public:
    domain::CommunicationService* service = ServiceRegistry::communicationService();

    QMap<dao::LinkDescriptionPtr, CommunicationLinkPresenter*> linkPresenters;
};

CommunicationsPresenter::CommunicationsPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    connect(d->service, &CommunicationService::descriptionAdded,
            this, &CommunicationsPresenter::onLinkAdded);
    connect(d->service, &CommunicationService::descriptionChanged,
            this, &CommunicationsPresenter::onLinkChanged);
    connect(d->service, &CommunicationService::linkStatisticsChanged,
            this, &CommunicationsPresenter::onLinkStatisticsChanged);
    connect(d->service, &CommunicationService::descriptionRemoved,
            this, &CommunicationsPresenter::onLinkRemoved);

    for (const dao::LinkDescriptionPtr& description: d->service->descriptions())
    {
        d->linkPresenters[description] = new CommunicationLinkPresenter(description, this);
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

void CommunicationsPresenter::onLinkAdded(const dao::LinkDescriptionPtr& description)
{
    d->linkPresenters[description] = new CommunicationLinkPresenter(description, this);

    this->updateCommunicationsLinks();
}

void CommunicationsPresenter::onLinkChanged(const dao::LinkDescriptionPtr& description)
{
    if (!d->linkPresenters.contains(description)) return;
    d->linkPresenters[description]->updateView();
}

void CommunicationsPresenter::onLinkStatisticsChanged(const dao::LinkDescriptionPtr& description)
{
    if (!d->linkPresenters.contains(description)) return;
    d->linkPresenters[description]->updateStatistics();
}

void CommunicationsPresenter::onLinkRemoved(const dao::LinkDescriptionPtr& description)
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
    auto description = dao::LinkDescriptionPtr::create();

    description->setName(tr("New UDP Link"));
    description->setType(dao::LinkDescription::Udp);
    description->setPort(settings::Provider::value(settings::communication::port).toInt());

    d->service->save(description);
}

void CommunicationsPresenter::onAddSerialLink()
{
    auto description = dao::LinkDescriptionPtr::create();

    description->setName(tr("New Serial Link"));
    description->setType(dao::LinkDescription::Serial);
    description->setBaudRate(settings::Provider::value(settings::communication::baudRate).toInt());

    d->service->save(description);
}
