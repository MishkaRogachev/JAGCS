#include "communication_settings_presenter.h"

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

class CommunicationSettingsPresenter::Impl
{
public:
    domain::CommunicationService* service;

    QMap<dao::LinkDescriptionPtr, CommunicationLinkPresenter*> linkPresenters;
};

CommunicationSettingsPresenter::CommunicationSettingsPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->service = ServiceRegistry::communicationService();

    connect(d->service, &CommunicationService::descriptionAdded,
            this, &CommunicationSettingsPresenter::onLinkAdded);
    connect(d->service, &CommunicationService::descriptionChanged,
            this, &CommunicationSettingsPresenter::onLinkChanged);
    connect(d->service, &CommunicationService::descriptionRemoved,
            this, &CommunicationSettingsPresenter::onLinkRemoved);
    connect(d->service, &CommunicationService::linkStatisticsChanged,
            this, &CommunicationSettingsPresenter::onLinkStatisticsChanged);

    for (const dao::LinkDescriptionPtr& description: d->service->descriptions())
    {
        d->linkPresenters[description] = new CommunicationLinkPresenter(
                                             d->service, description, this);
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
    d->linkPresenters[description] = new CommunicationLinkPresenter(
                                         d->service, description, this);

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

    d->service->save(description);
}

void CommunicationSettingsPresenter::onAddSerialLink()
{
    auto description = dao::LinkDescriptionPtr::create();

    description->setName(tr("New Serial Link"));
    description->setType(dao::LinkDescription::Serial);
    description->setBaudRate(settings::Provider::value(settings::communication::baudRate).toInt());

    d->service->save(description);
}
