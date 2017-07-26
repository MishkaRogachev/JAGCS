#include "communication_service.h"

// Qt
#include <QMap>
#include <QDebug>


// Internal
#include "link_description.h"

#include "generic_repository.h"
#include "generic_repository_impl.h"

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
    GenericRepository<dao::LinkDescription> linkRepository;

    QMap<dao::LinkDescriptionPtr, AbstractLink*> descriptedLinks;

    Impl():
        linkRepository("links")
    {}

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
                                           QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->communicator = commFactory->create();

    for (const dao::LinkDescriptionPtr& description: this->descriptions())
    {
        AbstractLink* link = d->linkFromDescription(description);
        link->setParent(this);
        connect(link, &AbstractLink::statisticsChanged,
                this, &CommunicationService::onLinkStatisticsChanged);
    }
}

CommunicationService::~CommunicationService()
{}

dao::LinkDescriptionPtr CommunicationService::description(int id, bool reload)
{
    return d->linkRepository.read(id, reload);
}

dao::LinkDescriptionPtrList CommunicationService::descriptions(const QString& condition, bool reload)
{
    dao::LinkDescriptionPtrList list;

    for (int id: d->linkRepository.selectId(condition))
    {
        list.append(this->description(id, reload));
    }

    return list;
}

bool CommunicationService::save(const dao::LinkDescriptionPtr& description)
{
    bool isNew = description->id() == 0;
    if (!d->linkRepository.save(description)) return false;

    isNew ? descriptionAdded(description) : descriptionChanged(description);

    if (d->descriptedLinks.contains(description))
    {
        AbstractLink* link = d->descriptedLinks[description];
        d->updateLinkFromDescription(link, description);

        emit link->statisticsChanged();
    }
    else
    {
        AbstractLink* link = d->linkFromDescription(description);
        link->setParent(this);
        connect(link, &AbstractLink::statisticsChanged,
                this, &CommunicationService::onLinkStatisticsChanged);
        emit link->statisticsChanged();
    }

    return true;
}

bool CommunicationService::remove(const dao::LinkDescriptionPtr& description)
{
    if (!d->linkRepository.remove(description)) return false;

    if (d->descriptedLinks.contains(description))
    {
        AbstractLink* link = d->descriptedLinks.take(description);

        d->communicator->removeLink(link);
        delete link;
    }

    emit descriptionRemoved(description);
    return true;
}

void CommunicationService::setLinkConnected(const dao::LinkDescriptionPtr& description,
                                            bool connected)
{
    AbstractLink* link = d->descriptedLinks[description];
    if (!link) return;

    link->setConnected(connected);
    link->statisticsChanged();
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
