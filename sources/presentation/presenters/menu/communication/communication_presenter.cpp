#include "communication_presenter.h"

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "link_description.h"

#include "service_registry.h"
#include "communication_service.h"

using namespace presentation;

CommunicationPresenter::CommunicationPresenter(QObject* parent):
    BasePresenter(parent),
    m_service(domain::ServiceRegistry::communicationService())
{
    connect(m_service, &domain::CommunicationService::descriptionAdded,
            this, &CommunicationPresenter::updateLinks);
    connect(m_service, &domain::CommunicationService::descriptionRemoved,
            this, &CommunicationPresenter::updateLinks);
}

void CommunicationPresenter::updateLinks()
{
    QVariantList linkIds;
    for (const dao::LinkDescriptionPtr& link: m_service->descriptions())
    {
        linkIds.append(link->id());
    }

    this->setViewProperty(PROPERTY(linkIds), linkIds);
}

void CommunicationPresenter::addUdpLink()
{
    auto description = dao::LinkDescriptionPtr::create();

    description->setName(tr("New UDP Link"));
    description->setType(dao::LinkDescription::Udp);
    description->setPort(settings::Provider::value(settings::communication::port).toInt());

    m_service->save(description);
}

void CommunicationPresenter::addSerialLink()
{
    auto description = dao::LinkDescriptionPtr::create();

    description->setName(tr("New Serial Link"));
    description->setType(dao::LinkDescription::Serial);
    description->setBaudRate(settings::Provider::value(settings::communication::baudRate).toInt());

    m_service->save(description);
}
