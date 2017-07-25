#include "communication_service.h"

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "db_facade.h"
#include "link_description.h"

#include "abstract_communicator.h"
#include "abstract_link.h"
#include "description_link_factory.h"

#include "i_communicator_factory.h"

using namespace comm;
using namespace domain;

class CommunicationService::Impl
{
public:
    AbstractCommunicator* communicator;
    db::DbFacade* dbFacade;

    QMap<dao::LinkDescriptionPtr, AbstractLink*> descriptedLinks;

    AbstractLink* linkFromDescription(const dao::LinkDescriptionPtr& description)
    {
        DescriptionLinkFactory factory(description);
        AbstractLink* link = factory.create();
        if (!link) return nullptr;

        descriptedLinks[description] = link;
        communicator->addLink(link);

        if (description->isAutoConnect()) link->connectLink();

        return link;
    }

    void updateLinkFromDescription(AbstractLink* link,
                                   const dao::LinkDescriptionPtr& description)
    {
        DescriptionLinkFactory factory(description);
        factory.update(link);
    }
};

CommunicationService::CommunicationService(ICommunicatorFactory* commFactory,
                                           db::DbFacade* facade,
                                           QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->communicator = commFactory->create();
    d->dbFacade = facade;

    for (const dao::LinkDescriptionPtr& description: facade->links())
        this->onLinkAdded(description);

    connect(d->dbFacade, &dao::DbFacade::linkAdded, this, &CommunicationService::onLinkAdded);
    connect(d->dbFacade, &dao::DbFacade::linkRemoved, this, &CommunicationService::onLinkRemoved);
    connect(d->dbFacade, &dao::DbFacade::linkChanged, this, &CommunicationService::onLinkChanged);
}

CommunicationService::~CommunicationService()
{
    for (const dao::LinkDescriptionPtr& link: d->descriptedLinks.keys())
    {
        link->setAutoConnect(link->isConnected());
        d->dbFacade->save(link);
    }
}

void CommunicationService::setLinkConnected(const dao::LinkDescriptionPtr& description,
                                            bool connected)
{
    AbstractLink* link = d->descriptedLinks[description];
    if (!link) return;

    link->setConnected(connected);
    link->statisticsChanged();
}

void CommunicationService::onLinkAdded(const dao::LinkDescriptionPtr& description)
{
    AbstractLink* link = d->linkFromDescription(description);
    link->setParent(this);
    connect(link, &AbstractLink::statisticsChanged,
            this, &CommunicationService::onLinkStatisticsChanged);
    link->statisticsChanged();
}

void CommunicationService::onLinkChanged(const dao::LinkDescriptionPtr& description)
{
    AbstractLink* link = d->descriptedLinks[description];
    if (!link) return;
    d->updateLinkFromDescription(link, description);
    link->statisticsChanged();
}

void CommunicationService::onLinkRemoved(const dao::LinkDescriptionPtr& description)
{
    if (!d->descriptedLinks.contains(description)) return;
    AbstractLink* link = d->descriptedLinks.take(description);

    d->communicator->removeLink(link);
    delete link;
}

void CommunicationService::onLinkStatisticsChanged()
{
    AbstractLink* link = qobject_cast<AbstractLink*>(this->sender());
    dao::LinkDescriptionPtr description = d->descriptedLinks.key(link);
    if (description.isNull()) return;

    description->setBytesRecvSec(link->bytesReceivedSec());
    description->setBytesSentSec(link->bytesSentSec());
    description->setConnected(link->isConnected());

    emit linkStatisticsChanged(description);
}
