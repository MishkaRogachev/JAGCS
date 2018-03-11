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
    for (const dao::LinkDescriptionPtr& link: m_service->descriptions())
    {
        linkIds.append(link->id());
    }

    this->setViewProperty(PROPERTY(linkIds), linkIds);
}

void LinkListPresenter::addUdpLink()
{
    dao::LinkDescriptionPtr description = dao::LinkDescriptionPtr::create();

    description->setName(tr("New UDP Link"));
    description->setType(dao::LinkDescription::Udp);
    description->setParameter(dao::LinkDescription::Port,
                              settings::Provider::value(settings::communication::port));

    m_service->save(description);
}

void LinkListPresenter::addSerialLink()
{
    dao::LinkDescriptionPtr description = dao::LinkDescriptionPtr::create();

    description->setName(tr("New Serial Link"));
    description->setType(dao::LinkDescription::Serial);
    description->setParameter(dao::LinkDescription::BaudRate,
                              settings::Provider::value(settings::communication::baudRate));

    m_service->save(description);
}
