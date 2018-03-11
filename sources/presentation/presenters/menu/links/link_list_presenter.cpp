#include "link_list_presenter.h"

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "link_description.h"

#include "service_registry.h"
#include "communication_service.h"

using namespace presentation;

LinkListPresenter::LinkListPresenter(QObject* parent):
    BasePresenter(parent),
    m_service(domain::ServiceRegistry::communicationService())
{
    connect(m_service, &domain::CommunicationService::descriptionAdded,
            this, &LinkListPresenter::updateLinks);
    connect(m_service, &domain::CommunicationService::descriptionRemoved,
            this, &LinkListPresenter::updateLinks);
}

void LinkListPresenter::updateLinks()
{
    QVariantList linkIds;
    for (const dto::LinkDescriptionPtr& link: m_service->descriptions())
    {
        linkIds.append(link->id());
    }

    this->setViewProperty(PROPERTY(linkIds), linkIds);
}

void LinkListPresenter::addUdpLink()
{
    dto::LinkDescriptionPtr description = dto::LinkDescriptionPtr::create();

    description->setName(tr("New UDP Link"));
    description->setType(dto::LinkDescription::Udp);
    description->setParameter(dto::LinkDescription::Port,
                              settings::Provider::value(settings::communication::port));

    m_service->save(description);
}

void LinkListPresenter::addSerialLink()
{
    dto::LinkDescriptionPtr description = dto::LinkDescriptionPtr::create();

    description->setName(tr("New Serial Link"));
    description->setType(dto::LinkDescription::Serial);
    description->setParameter(dto::LinkDescription::BaudRate,
                              settings::Provider::value(settings::communication::baudRate));

    m_service->save(description);
}
