#include "communication_presenter.h"

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

class CommunicationPresenter::Impl
{
public:
    domain::CommunicationService* service = ServiceRegistry::communicationService();

    QMap<dao::LinkDescriptionPtr, CommunicationLinkPresenter*> linkPresenters;
};

CommunicationPresenter::CommunicationPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    connect(d->service, &CommunicationService::descriptionAdded,
            this, &CommunicationPresenter::onLinkAdded);
    connect(d->service, &CommunicationService::descriptionChanged,
            this, &CommunicationPresenter::onLinkChanged);
    connect(d->service, &CommunicationService::linkStatisticsChanged,
            this, &CommunicationPresenter::onLinkStatisticsChanged);
    connect(d->service, &CommunicationService::descriptionRemoved,
            this, &CommunicationPresenter::onLinkRemoved);

    for (const dao::LinkDescriptionPtr& description: d->service->descriptions())
    {
        d->linkPresenters[description] = new CommunicationLinkPresenter(description, this);
    }
}

CommunicationPresenter::~CommunicationPresenter()
{}

void CommunicationPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(addUdpLink()), this, SLOT(onAddUdpLink()));
    connect(view, SIGNAL(addSerialLink()), this, SLOT(onAddSerialLink()));

    this->updateCommunicationsLinks();
}

void CommunicationPresenter::onLinkAdded(const dao::LinkDescriptionPtr& description)
{
    d->linkPresenters[description] = new CommunicationLinkPresenter(description, this);

    this->updateCommunicationsLinks();
}

void CommunicationPresenter::onLinkChanged(const dao::LinkDescriptionPtr& description)
{
    if (!d->linkPresenters.contains(description)) return;
    d->linkPresenters[description]->updateView();
}

void CommunicationPresenter::onLinkStatisticsChanged(const dao::LinkDescriptionPtr& description)
{
    if (!d->linkPresenters.contains(description)) return;
    d->linkPresenters[description]->updateStatistics();
}

void CommunicationPresenter::onLinkRemoved(const dao::LinkDescriptionPtr& description)
{
    if (!d->linkPresenters.contains(description)) return;
    CommunicationLinkPresenter* linkPresenter = d->linkPresenters.take(description);

    delete linkPresenter;
    this->updateCommunicationsLinks();
}

void CommunicationPresenter::updateCommunicationsLinks()
{
    QList<QObject*> objectList;
    for (CommunicationLinkPresenter* linkPresenter: d->linkPresenters.values())
    {
        objectList.append(linkPresenter);
    }

    this->setViewProperty(PROPERTY(links), QVariant::fromValue(objectList));
}

void CommunicationPresenter::onAddUdpLink()
{
    auto description = dao::LinkDescriptionPtr::create();

    description->setName(tr("New UDP Link"));
    description->setType(dao::LinkDescription::Udp);
    description->setPort(settings::Provider::value(settings::communication::port).toInt());

    d->service->save(description);
}

void CommunicationPresenter::onAddSerialLink()
{
    auto description = dao::LinkDescriptionPtr::create();

    description->setName(tr("New Serial Link"));
    description->setType(dao::LinkDescription::Serial);
    description->setBaudRate(settings::Provider::value(settings::communication::baudRate).toInt());

    d->service->save(description);
}
